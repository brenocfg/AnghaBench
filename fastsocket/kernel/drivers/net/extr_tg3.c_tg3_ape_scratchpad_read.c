#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u32 ;
struct tg3 {int dummy; } ;

/* Variables and functions */
 scalar_t__ APE_EVENT_1 ; 
 scalar_t__ APE_EVENT_STATUS_DRIVER_EVNT ; 
 scalar_t__ APE_EVENT_STATUS_EVENT_PENDING ; 
 scalar_t__ APE_EVENT_STATUS_SCRTCHPD_READ ; 
 scalar_t__ APE_FW_STATUS_READY ; 
 int /*<<< orphan*/  APE_HAS_NCSI ; 
 scalar_t__ APE_SEG_SIG_MAGIC ; 
 int EAGAIN ; 
 int ENODEV ; 
 scalar_t__ TG3_APE_EVENT ; 
 scalar_t__ TG3_APE_EVENT_STATUS ; 
 scalar_t__ TG3_APE_FW_STATUS ; 
 int /*<<< orphan*/  TG3_APE_LOCK_MEM ; 
 scalar_t__ TG3_APE_SEG_MSG_BUF_LEN ; 
 scalar_t__ TG3_APE_SEG_MSG_BUF_OFF ; 
 scalar_t__ TG3_APE_SEG_SIG ; 
 scalar_t__ TG3_APE_SHMEM_BASE ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 
 int tg3_ape_event_lock (struct tg3*,int) ; 
 scalar_t__ tg3_ape_read32 (struct tg3*,scalar_t__) ; 
 int /*<<< orphan*/  tg3_ape_unlock (struct tg3*,int /*<<< orphan*/ ) ; 
 scalar_t__ tg3_ape_wait_for_event (struct tg3*,int) ; 
 int /*<<< orphan*/  tg3_ape_write32 (struct tg3*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  tg3_flag (struct tg3*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tg3_ape_scratchpad_read(struct tg3 *tp, u32 *data, u32 base_off,
				   u32 len)
{
	int err;
	u32 i, bufoff, msgoff, maxlen, apedata;

	if (!tg3_flag(tp, APE_HAS_NCSI))
		return 0;

	apedata = tg3_ape_read32(tp, TG3_APE_SEG_SIG);
	if (apedata != APE_SEG_SIG_MAGIC)
		return -ENODEV;

	apedata = tg3_ape_read32(tp, TG3_APE_FW_STATUS);
	if (!(apedata & APE_FW_STATUS_READY))
		return -EAGAIN;

	bufoff = tg3_ape_read32(tp, TG3_APE_SEG_MSG_BUF_OFF) +
		 TG3_APE_SHMEM_BASE;
	msgoff = bufoff + 2 * sizeof(u32);
	maxlen = tg3_ape_read32(tp, TG3_APE_SEG_MSG_BUF_LEN);

	while (len) {
		u32 length;

		/* Cap xfer sizes to scratchpad limits. */
		length = (len > maxlen) ? maxlen : len;
		len -= length;

		apedata = tg3_ape_read32(tp, TG3_APE_FW_STATUS);
		if (!(apedata & APE_FW_STATUS_READY))
			return -EAGAIN;

		/* Wait for up to 1 msec for APE to service previous event. */
		err = tg3_ape_event_lock(tp, 1000);
		if (err)
			return err;

		apedata = APE_EVENT_STATUS_DRIVER_EVNT |
			  APE_EVENT_STATUS_SCRTCHPD_READ |
			  APE_EVENT_STATUS_EVENT_PENDING;
		tg3_ape_write32(tp, TG3_APE_EVENT_STATUS, apedata);

		tg3_ape_write32(tp, bufoff, base_off);
		tg3_ape_write32(tp, bufoff + sizeof(u32), length);

		tg3_ape_unlock(tp, TG3_APE_LOCK_MEM);
		tg3_ape_write32(tp, TG3_APE_EVENT, APE_EVENT_1);

		base_off += length;

		if (tg3_ape_wait_for_event(tp, 30000))
			return -EAGAIN;

		for (i = 0; length; i += 4, length -= 4) {
			u32 val = tg3_ape_read32(tp, msgoff + i);
			memcpy(data, &val, sizeof(u32));
			data++;
		}
	}

	return 0;
}