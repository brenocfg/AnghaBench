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
typedef  int u8 ;
typedef  int u16 ;
struct if_sdio_card {int* buffer; int /*<<< orphan*/  ioport; int /*<<< orphan*/  func; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
 unsigned long HZ ; 
 int IF_SDIO_IO_RDY ; 
 int /*<<< orphan*/  IF_SDIO_STATUS ; 
 int /*<<< orphan*/  LBS_DEB_SDIO ; 
#define  MVMS_CMD 130 
#define  MVMS_DAT 129 
#define  MVMS_EVENT 128 
 int if_sdio_handle_cmd (struct if_sdio_card*,int*,int) ; 
 int if_sdio_handle_data (struct if_sdio_card*,int*,int) ; 
 int if_sdio_handle_event (struct if_sdio_card*,int*,int) ; 
 int if_sdio_read_rx_len (struct if_sdio_card*,int*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lbs_deb_sdio (char*,int,...) ; 
 int /*<<< orphan*/  lbs_pr_err (char*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int sdio_align_size (int /*<<< orphan*/ ,int) ; 
 int sdio_readb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int sdio_readsb (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int if_sdio_card_to_host(struct if_sdio_card *card)
{
	int ret;
	u8 status;
	u16 size, type, chunk;
	unsigned long timeout;

	lbs_deb_enter(LBS_DEB_SDIO);

	size = if_sdio_read_rx_len(card, &ret);
	if (ret)
		goto out;

	if (size < 4) {
		lbs_deb_sdio("invalid packet size (%d bytes) from firmware\n",
			(int)size);
		ret = -EINVAL;
		goto out;
	}

	timeout = jiffies + HZ;
	while (1) {
		status = sdio_readb(card->func, IF_SDIO_STATUS, &ret);
		if (ret)
			goto out;
		if (status & IF_SDIO_IO_RDY)
			break;
		if (time_after(jiffies, timeout)) {
			ret = -ETIMEDOUT;
			goto out;
		}
		mdelay(1);
	}

	/*
	 * The transfer must be in one transaction or the firmware
	 * goes suicidal. There's no way to guarantee that for all
	 * controllers, but we can at least try.
	 */
	chunk = sdio_align_size(card->func, size);

	ret = sdio_readsb(card->func, card->buffer, card->ioport, chunk);
	if (ret)
		goto out;

	chunk = card->buffer[0] | (card->buffer[1] << 8);
	type = card->buffer[2] | (card->buffer[3] << 8);

	lbs_deb_sdio("packet of type %d and size %d bytes\n",
		(int)type, (int)chunk);

	if (chunk > size) {
		lbs_deb_sdio("packet fragment (%d > %d)\n",
			(int)chunk, (int)size);
		ret = -EINVAL;
		goto out;
	}

	if (chunk < size) {
		lbs_deb_sdio("packet fragment (%d < %d)\n",
			(int)chunk, (int)size);
	}

	switch (type) {
	case MVMS_CMD:
		ret = if_sdio_handle_cmd(card, card->buffer + 4, chunk - 4);
		if (ret)
			goto out;
		break;
	case MVMS_DAT:
		ret = if_sdio_handle_data(card, card->buffer + 4, chunk - 4);
		if (ret)
			goto out;
		break;
	case MVMS_EVENT:
		ret = if_sdio_handle_event(card, card->buffer + 4, chunk - 4);
		if (ret)
			goto out;
		break;
	default:
		lbs_deb_sdio("invalid type (%d) from firmware\n",
				(int)type);
		ret = -EINVAL;
		goto out;
	}

out:
	if (ret)
		lbs_pr_err("problem fetching packet from firmware\n");

	lbs_deb_leave_args(LBS_DEB_SDIO, "ret %d", ret);

	return ret;
}