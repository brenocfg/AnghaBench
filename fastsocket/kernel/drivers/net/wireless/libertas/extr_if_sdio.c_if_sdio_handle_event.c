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
typedef  int u32 ;
struct if_sdio_card {scalar_t__ model; int /*<<< orphan*/  priv; int /*<<< orphan*/  func; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IF_SDIO_EVENT ; 
 scalar_t__ IF_SDIO_MODEL_8385 ; 
 int /*<<< orphan*/  LBS_DEB_SDIO ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lbs_deb_sdio (char*,int) ; 
 int /*<<< orphan*/  lbs_queue_event (int /*<<< orphan*/ ,int) ; 
 int sdio_readb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int if_sdio_handle_event(struct if_sdio_card *card,
		u8 *buffer, unsigned size)
{
	int ret;
	u32 event;

	lbs_deb_enter(LBS_DEB_SDIO);

	if (card->model == IF_SDIO_MODEL_8385) {
		event = sdio_readb(card->func, IF_SDIO_EVENT, &ret);
		if (ret)
			goto out;

		/* right shift 3 bits to get the event id */
		event >>= 3;
	} else {
		if (size < 4) {
			lbs_deb_sdio("event packet too small (%d bytes)\n",
				(int)size);
			ret = -EINVAL;
			goto out;
		}
		event = buffer[3] << 24;
		event |= buffer[2] << 16;
		event |= buffer[1] << 8;
		event |= buffer[0] << 0;
	}

	lbs_queue_event(card->priv, event & 0xFF);
	ret = 0;

out:
	lbs_deb_leave_args(LBS_DEB_SDIO, "ret %d", ret);

	return ret;
}