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
struct tg3_napi {scalar_t__ tx_cons; scalar_t__* rx_rcb_prod_idx; scalar_t__ rx_rcb_ptr; struct tg3_hw_status* hw_status; struct tg3* tp; } ;
struct tg3_hw_status {int status; TYPE_1__* idx; } ;
struct tg3 {int dummy; } ;
struct TYPE_2__ {scalar_t__ tx_consumer; } ;

/* Variables and functions */
 int /*<<< orphan*/  POLL_SERDES ; 
 int SD_STATUS_LINK_CHG ; 
 int /*<<< orphan*/  USE_LINKCHG_REG ; 
 scalar_t__ tg3_flag (struct tg3*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int tg3_has_work(struct tg3_napi *tnapi)
{
	struct tg3 *tp = tnapi->tp;
	struct tg3_hw_status *sblk = tnapi->hw_status;
	unsigned int work_exists = 0;

	/* check for phy events */
	if (!(tg3_flag(tp, USE_LINKCHG_REG) || tg3_flag(tp, POLL_SERDES))) {
		if (sblk->status & SD_STATUS_LINK_CHG)
			work_exists = 1;
	}

	/* check for TX work to do */
	if (sblk->idx[0].tx_consumer != tnapi->tx_cons)
		work_exists = 1;

	/* check for RX work to do */
	if (tnapi->rx_rcb_prod_idx &&
	    *(tnapi->rx_rcb_prod_idx) != tnapi->rx_rcb_ptr)
		work_exists = 1;

	return work_exists;
}