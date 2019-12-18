#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct et131x_adapter {int PacketFilter; TYPE_6__* regs; } ;
struct TYPE_9__ {int pkt_filter_disable; } ;
struct TYPE_16__ {void* value; TYPE_1__ bits; } ;
struct TYPE_10__ {int filter_broad_en; int filter_multi_en; int filter_uni_en; } ;
struct TYPE_15__ {void* value; TYPE_2__ bits; } ;
struct TYPE_12__ {int /*<<< orphan*/  value; } ;
struct TYPE_11__ {int /*<<< orphan*/  value; } ;
struct TYPE_13__ {TYPE_4__ ctrl; TYPE_3__ pf_ctrl; } ;
struct TYPE_14__ {TYPE_5__ rxmac; } ;
typedef  TYPE_7__ RXMAC_PF_CTRL_t ;
typedef  TYPE_8__ RXMAC_CTRL_t ;

/* Variables and functions */
 int ET131X_PACKET_TYPE_ALL_MULTICAST ; 
 int ET131X_PACKET_TYPE_BROADCAST ; 
 int ET131X_PACKET_TYPE_DIRECTED ; 
 int ET131X_PACKET_TYPE_PROMISCUOUS ; 
 int /*<<< orphan*/  SetupDeviceForMulticast (struct et131x_adapter*) ; 
 int /*<<< orphan*/  SetupDeviceForUnicast (struct et131x_adapter*) ; 
 void* readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (void*,int /*<<< orphan*/ *) ; 

int et131x_set_packet_filter(struct et131x_adapter *adapter)
{
	int status = 0;
	uint32_t filter = adapter->PacketFilter;
	RXMAC_CTRL_t ctrl;
	RXMAC_PF_CTRL_t pf_ctrl;

	ctrl.value = readl(&adapter->regs->rxmac.ctrl.value);
	pf_ctrl.value = readl(&adapter->regs->rxmac.pf_ctrl.value);

	/* Default to disabled packet filtering.  Enable it in the individual
	 * case statements that require the device to filter something
	 */
	ctrl.bits.pkt_filter_disable = 1;

	/* Set us to be in promiscuous mode so we receive everything, this
	 * is also true when we get a packet filter of 0
	 */
	if ((filter & ET131X_PACKET_TYPE_PROMISCUOUS) || filter == 0) {
		pf_ctrl.bits.filter_broad_en = 0;
		pf_ctrl.bits.filter_multi_en = 0;
		pf_ctrl.bits.filter_uni_en = 0;
	} else {
		/*
		 * Set us up with Multicast packet filtering.  Three cases are
		 * possible - (1) we have a multi-cast list, (2) we receive ALL
		 * multicast entries or (3) we receive none.
		 */
		if (filter & ET131X_PACKET_TYPE_ALL_MULTICAST) {
			pf_ctrl.bits.filter_multi_en = 0;
		} else {
			SetupDeviceForMulticast(adapter);
			pf_ctrl.bits.filter_multi_en = 1;
			ctrl.bits.pkt_filter_disable = 0;
		}

		/* Set us up with Unicast packet filtering */
		if (filter & ET131X_PACKET_TYPE_DIRECTED) {
			SetupDeviceForUnicast(adapter);
			pf_ctrl.bits.filter_uni_en = 1;
			ctrl.bits.pkt_filter_disable = 0;
		}

		/* Set us up with Broadcast packet filtering */
		if (filter & ET131X_PACKET_TYPE_BROADCAST) {
			pf_ctrl.bits.filter_broad_en = 1;
			ctrl.bits.pkt_filter_disable = 0;
		} else {
			pf_ctrl.bits.filter_broad_en = 0;
		}

		/* Setup the receive mac configuration registers - Packet
		 * Filter control + the enable / disable for packet filter
		 * in the control reg.
		 */
		writel(pf_ctrl.value,
		       &adapter->regs->rxmac.pf_ctrl.value);
		writel(ctrl.value, &adapter->regs->rxmac.ctrl.value);
	}
	return status;
}