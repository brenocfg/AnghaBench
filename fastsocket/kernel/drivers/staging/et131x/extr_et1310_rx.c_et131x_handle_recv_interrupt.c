#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct sk_buff {int dummy; } ;
struct TYPE_12__ {scalar_t__ nReadyRecv; int UnfinishedReceives; int /*<<< orphan*/  RecvList; } ;
struct TYPE_8__ {int /*<<< orphan*/  ipackets; } ;
struct et131x_adapter {int Flags; TYPE_5__ RxRing; TYPE_4__* regs; TYPE_2__* pdev; TYPE_1__ Stats; int /*<<< orphan*/  PacketFilter; } ;
struct TYPE_13__ {scalar_t__ PacketSize; struct sk_buff* Packet; } ;
struct TYPE_10__ {int /*<<< orphan*/  watchdog_timer; } ;
struct TYPE_11__ {TYPE_3__ global; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;
typedef  TYPE_6__* PMP_RFD ;

/* Variables and functions */
 int NANO_IN_A_MICRO ; 
 int NUM_PACKETS_HANDLED ; 
 int PARM_TX_TIME_INT_DEF ; 
 scalar_t__ RFD_LOW_WATER_MARK ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int fMP_ADAPTER_LINK_DETECTION ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 TYPE_6__* nic_rx_pkts (struct et131x_adapter*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

void et131x_handle_recv_interrupt(struct et131x_adapter *etdev)
{
	PMP_RFD pMpRfd = NULL;
	struct sk_buff *PacketArray[NUM_PACKETS_HANDLED];
	PMP_RFD RFDFreeArray[NUM_PACKETS_HANDLED];
	uint32_t PacketArrayCount = 0;
	uint32_t PacketsToHandle;
	uint32_t PacketFreeCount = 0;
	bool TempUnfinishedRec = false;

	PacketsToHandle = NUM_PACKETS_HANDLED;

	/* Process up to available RFD's */
	while (PacketArrayCount < PacketsToHandle) {
		if (list_empty(&etdev->RxRing.RecvList)) {
			WARN_ON(etdev->RxRing.nReadyRecv != 0);
			TempUnfinishedRec = true;
			break;
		}

		pMpRfd = nic_rx_pkts(etdev);

		if (pMpRfd == NULL)
			break;

		/* Do not receive any packets until a filter has been set.
		 * Do not receive any packets until we have link.
		 * If length is zero, return the RFD in order to advance the
		 * Free buffer ring.
		 */
		if (!etdev->PacketFilter ||
		    !(etdev->Flags & fMP_ADAPTER_LINK_DETECTION) ||
		    pMpRfd->PacketSize == 0) {
			continue;
		}

		/* Increment the number of packets we received */
		etdev->Stats.ipackets++;

		/* Set the status on the packet, either resources or success */
		if (etdev->RxRing.nReadyRecv >= RFD_LOW_WATER_MARK) {
			/* Put this RFD on the pending list
			 *
			 * NOTE: nic_rx_pkts() above is already returning the
			 * RFD to the RecvList, so don't additionally do that
			 * here.
			 * Besides, we don't really need (at this point) the
			 * pending list anyway.
			 */
		} else {
			RFDFreeArray[PacketFreeCount] = pMpRfd;
			PacketFreeCount++;

			dev_warn(&etdev->pdev->dev,
				    "RFD's are running out\n");
		}

		PacketArray[PacketArrayCount] = pMpRfd->Packet;
		PacketArrayCount++;
	}

	if ((PacketArrayCount == NUM_PACKETS_HANDLED) || TempUnfinishedRec) {
		etdev->RxRing.UnfinishedReceives = true;
		writel(PARM_TX_TIME_INT_DEF * NANO_IN_A_MICRO,
		       &etdev->regs->global.watchdog_timer);
	} else {
		/* Watchdog timer will disable itself if appropriate. */
		etdev->RxRing.UnfinishedReceives = false;
	}
}