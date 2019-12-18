#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* read ) (struct ixgbe_hw*,int*,int) ;int /*<<< orphan*/  (* check_for_msg ) (struct ixgbe_hw*) ;int /*<<< orphan*/  (* check_for_ack ) (struct ixgbe_hw*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  v2p_mailbox; TYPE_2__ ops; } ;
struct TYPE_4__ {int get_link_status; } ;
struct ixgbe_hw {TYPE_3__ mbx; TYPE_1__ mac; } ;
struct ixgbevf_adapter {int link_up; int /*<<< orphan*/  eims_other; int /*<<< orphan*/  watchdog_timer; struct ixgbe_hw hw; struct pci_dev* pdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int IXGBE_MBVFICR_VFREQ_MASK ; 
 int IXGBE_PF_CONTROL_MSG ; 
 int /*<<< orphan*/  IXGBE_VFMAILBOX_PFACK ; 
 int /*<<< orphan*/  IXGBE_VFMAILBOX_PFSTS ; 
 int /*<<< orphan*/  IXGBE_VTEIMS ; 
 int IXGBE_VT_MSGTYPE_NACK ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  stub3 (struct ixgbe_hw*,int*,int) ; 

__attribute__((used)) static irqreturn_t ixgbevf_msix_other(int irq, void *data)
{
	struct ixgbevf_adapter *adapter = data;
	struct pci_dev *pdev = adapter->pdev;
	struct ixgbe_hw *hw = &adapter->hw;
	u32 msg;
	bool got_ack = false;

	hw->mac.get_link_status = 1;
	if (!hw->mbx.ops.check_for_ack(hw))
		got_ack = true;

	if (!hw->mbx.ops.check_for_msg(hw)) {
		hw->mbx.ops.read(hw, &msg, 1);

		if ((msg & IXGBE_MBVFICR_VFREQ_MASK) == IXGBE_PF_CONTROL_MSG) {
			mod_timer(&adapter->watchdog_timer,
				  round_jiffies(jiffies + 1));
			adapter->link_up = false;
		}

		if (msg & IXGBE_VT_MSGTYPE_NACK)
			dev_info(&pdev->dev,
				 "Last Request of type %2.2x to PF Nacked\n",
				 msg & 0xFF);
		hw->mbx.v2p_mailbox |= IXGBE_VFMAILBOX_PFSTS;
	}

	/* checking for the ack clears the PFACK bit.  Place
	 * it back in the v2p_mailbox cache so that anyone
	 * polling for an ack will not miss it
	 */
	if (got_ack)
		hw->mbx.v2p_mailbox |= IXGBE_VFMAILBOX_PFACK;

	IXGBE_WRITE_REG(hw, IXGBE_VTEIMS, adapter->eims_other);

	return IRQ_HANDLED;
}