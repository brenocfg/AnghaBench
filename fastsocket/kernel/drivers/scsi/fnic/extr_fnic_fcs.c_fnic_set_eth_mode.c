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
struct fnic {int state; int /*<<< orphan*/  fnic_lock; } ;
typedef  enum fnic_state { ____Placeholder_fnic_state } fnic_state ;

/* Variables and functions */
#define  FNIC_IN_ETH_MODE 131 
#define  FNIC_IN_ETH_TRANS_FC_MODE 130 
#define  FNIC_IN_FC_MODE 129 
#define  FNIC_IN_FC_TRANS_ETH_MODE 128 
 int fnic_fw_reset_handler (struct fnic*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void fnic_set_eth_mode(struct fnic *fnic)
{
	unsigned long flags;
	enum fnic_state old_state;
	int ret;

	spin_lock_irqsave(&fnic->fnic_lock, flags);
again:
	old_state = fnic->state;
	switch (old_state) {
	case FNIC_IN_FC_MODE:
	case FNIC_IN_ETH_TRANS_FC_MODE:
	default:
		fnic->state = FNIC_IN_FC_TRANS_ETH_MODE;
		spin_unlock_irqrestore(&fnic->fnic_lock, flags);

		ret = fnic_fw_reset_handler(fnic);

		spin_lock_irqsave(&fnic->fnic_lock, flags);
		if (fnic->state != FNIC_IN_FC_TRANS_ETH_MODE)
			goto again;
		if (ret)
			fnic->state = old_state;
		break;

	case FNIC_IN_FC_TRANS_ETH_MODE:
	case FNIC_IN_ETH_MODE:
		break;
	}
	spin_unlock_irqrestore(&fnic->fnic_lock, flags);
}