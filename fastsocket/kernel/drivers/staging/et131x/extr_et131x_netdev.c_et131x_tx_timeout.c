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
struct net_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ pTxDescRingVa; TYPE_3__* CurrSendHead; } ;
struct et131x_adapter {int Flags; int /*<<< orphan*/  TCBSendQLock; TYPE_2__* pdev; TYPE_1__ TxRing; } ;
struct TYPE_6__ {scalar_t__ Count; int /*<<< orphan*/  Flags; int /*<<< orphan*/  WrIndex; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  TX_DESC_ENTRY_t ;
typedef  TYPE_3__* PMP_TCB ;

/* Variables and functions */
 int INDEX10 (int /*<<< orphan*/ ) ; 
 scalar_t__ NIC_SEND_HANG_THRESHOLD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  et131x_close (struct net_device*) ; 
 int /*<<< orphan*/  et131x_open (struct net_device*) ; 
 int fMP_ADAPTER_HARDWARE_ERROR ; 
 int fMP_ADAPTER_LINK_DETECTION ; 
 int fMP_ADAPTER_NON_RECOVER_ERROR ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 
 struct et131x_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void et131x_tx_timeout(struct net_device *netdev)
{
	struct et131x_adapter *etdev = netdev_priv(netdev);
	PMP_TCB pMpTcb;
	unsigned long flags;

	/* Just skip this part if the adapter is doing link detection */
	if (etdev->Flags & fMP_ADAPTER_LINK_DETECTION)
		return;

	/* Any nonrecoverable hardware error?
	 * Checks adapter->flags for any failure in phy reading
	 */
	if (etdev->Flags & fMP_ADAPTER_NON_RECOVER_ERROR)
		return;

	/* Hardware failure? */
	if (etdev->Flags & fMP_ADAPTER_HARDWARE_ERROR) {
		dev_err(&etdev->pdev->dev, "hardware error - reset\n");
		return;
	}

	/* Is send stuck? */
	spin_lock_irqsave(&etdev->TCBSendQLock, flags);

	pMpTcb = etdev->TxRing.CurrSendHead;

	if (pMpTcb != NULL) {
		pMpTcb->Count++;

		if (pMpTcb->Count > NIC_SEND_HANG_THRESHOLD) {
			TX_DESC_ENTRY_t StuckDescriptors[10];

			if (INDEX10(pMpTcb->WrIndex) > 7) {
				memcpy(StuckDescriptors,
				       etdev->TxRing.pTxDescRingVa +
				       INDEX10(pMpTcb->WrIndex) - 6,
				       sizeof(TX_DESC_ENTRY_t) * 10);
			}

			spin_unlock_irqrestore(&etdev->TCBSendQLock,
					       flags);

			dev_warn(&etdev->pdev->dev,
				"Send stuck - reset.  pMpTcb->WrIndex %x, Flags 0x%08x\n",
				pMpTcb->WrIndex,
				pMpTcb->Flags);

			et131x_close(netdev);
			et131x_open(netdev);

			return;
		}
	}

	spin_unlock_irqrestore(&etdev->TCBSendQLock, flags);
}