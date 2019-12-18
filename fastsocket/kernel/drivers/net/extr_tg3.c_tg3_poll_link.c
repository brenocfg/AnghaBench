#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tg3_hw_status {int status; } ;
struct tg3 {int /*<<< orphan*/  lock; TYPE_1__* napi; } ;
struct TYPE_2__ {struct tg3_hw_status* hw_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_STATUS ; 
 int MAC_STATUS_CFG_CHANGED ; 
 int MAC_STATUS_LNKSTATE_CHANGED ; 
 int MAC_STATUS_MI_COMPLETION ; 
 int MAC_STATUS_SYNC_CHANGED ; 
 int /*<<< orphan*/  POLL_SERDES ; 
 int SD_STATUS_LINK_CHG ; 
 int SD_STATUS_UPDATED ; 
 int /*<<< orphan*/  USE_LINKCHG_REG ; 
 int /*<<< orphan*/  USE_PHYLIB ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ tg3_flag (struct tg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_setup_phy (struct tg3*,int) ; 
 int /*<<< orphan*/  tw32_f (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void tg3_poll_link(struct tg3 *tp)
{
	/* handle link change and other phy events */
	if (!(tg3_flag(tp, USE_LINKCHG_REG) || tg3_flag(tp, POLL_SERDES))) {
		struct tg3_hw_status *sblk = tp->napi[0].hw_status;

		if (sblk->status & SD_STATUS_LINK_CHG) {
			sblk->status = SD_STATUS_UPDATED |
				       (sblk->status & ~SD_STATUS_LINK_CHG);
			spin_lock(&tp->lock);
			if (tg3_flag(tp, USE_PHYLIB)) {
				tw32_f(MAC_STATUS,
				     (MAC_STATUS_SYNC_CHANGED |
				      MAC_STATUS_CFG_CHANGED |
				      MAC_STATUS_MI_COMPLETION |
				      MAC_STATUS_LNKSTATE_CHANGED));
				udelay(40);
			} else
				tg3_setup_phy(tp, false);
			spin_unlock(&tp->lock);
		}
	}
}