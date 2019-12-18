#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  void* uint32_t ;
typedef  int uint16_t ;
struct TYPE_9__ {int TransPhyComaModeOnBoot; } ;
struct et131x_adapter {scalar_t__ MediaState; int Flags; int RegistryPhyLoopbk; scalar_t__ linkspeed; int RegistryPhyComa; int AiForceDpx; int RegistryJumboPacket; TYPE_3__ PoMgmt; void* duplex_mode; int /*<<< orphan*/  netdev; int /*<<< orphan*/  Lock; TYPE_1__* pdev; } ;
struct TYPE_8__ {scalar_t__ auto_neg_complete; scalar_t__ link_status; } ;
struct TYPE_10__ {TYPE_2__ bits; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
typedef  TYPE_4__ MI_BMSR_t ;

/* Variables and functions */
 int /*<<< orphan*/  ConfigFlowControl (struct et131x_adapter*) ; 
 int /*<<< orphan*/  ConfigMACRegs2 (struct et131x_adapter*) ; 
 int /*<<< orphan*/  ET1310_PhyAndOrReg (struct et131x_adapter*,int,int,int) ; 
 int /*<<< orphan*/  ET1310_PhyLinkStatus (struct et131x_adapter*,int /*<<< orphan*/ *,void**,void**,void**,void**,void**,void**) ; 
 int /*<<< orphan*/  EnablePhyComa (struct et131x_adapter*) ; 
 int /*<<< orphan*/  MiRead (struct et131x_adapter*,int,int*) ; 
 int /*<<< orphan*/  MiWrite (struct et131x_adapter*,int,int) ; 
 scalar_t__ NETIF_STATUS_MEDIA_CONNECT ; 
 scalar_t__ NETIF_STATUS_MEDIA_DISCONNECT ; 
 int /*<<< orphan*/  SetRxDmaTimer (struct et131x_adapter*) ; 
 scalar_t__ TRUEPHY_SPEED_1000MBPS ; 
 scalar_t__ TRUEPHY_SPEED_10MBPS ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  et131x_adapter_setup (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_free_busy_send_packets (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_init_send (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_reset_recv (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_soft_reset (struct et131x_adapter*) ; 
 int fMP_ADAPTER_LINK_DETECTION ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void et131x_Mii_check(struct et131x_adapter *etdev,
		      MI_BMSR_t bmsr, MI_BMSR_t bmsr_ints)
{
	uint8_t link_status;
	uint32_t autoneg_status;
	uint32_t speed;
	uint32_t duplex;
	uint32_t mdi_mdix;
	uint32_t masterslave;
	uint32_t polarity;
	unsigned long flags;

	if (bmsr_ints.bits.link_status) {
		if (bmsr.bits.link_status) {
			etdev->PoMgmt.TransPhyComaModeOnBoot = 20;

			/* Update our state variables and indicate the
			 * connected state
			 */
			spin_lock_irqsave(&etdev->Lock, flags);

			etdev->MediaState = NETIF_STATUS_MEDIA_CONNECT;
			etdev->Flags &= ~fMP_ADAPTER_LINK_DETECTION;

			spin_unlock_irqrestore(&etdev->Lock, flags);

			/* Don't indicate state if we're in loopback mode */
			if (etdev->RegistryPhyLoopbk == false)
				netif_carrier_on(etdev->netdev);
		} else {
			dev_warn(&etdev->pdev->dev,
			    "Link down - cable problem ?\n");

			if (etdev->linkspeed == TRUEPHY_SPEED_10MBPS) {
				/* NOTE - Is there a way to query this without
				 * TruePHY?
				 * && TRU_QueryCoreType(etdev->hTruePhy, 0) == EMI_TRUEPHY_A13O) {
				 */
				uint16_t Register18;

				MiRead(etdev, 0x12, &Register18);
				MiWrite(etdev, 0x12, Register18 | 0x4);
				MiWrite(etdev, 0x10, Register18 | 0x8402);
				MiWrite(etdev, 0x11, Register18 | 511);
				MiWrite(etdev, 0x12, Register18);
			}

			/* For the first N seconds of life, we are in "link
			 * detection" When we are in this state, we should
			 * only report "connected". When the LinkDetection
			 * Timer expires, we can report disconnected (handled
			 * in the LinkDetectionDPC).
			 */
			if (!(etdev->Flags & fMP_ADAPTER_LINK_DETECTION) ||
			  (etdev->MediaState == NETIF_STATUS_MEDIA_DISCONNECT)) {
				spin_lock_irqsave(&etdev->Lock, flags);
				etdev->MediaState =
				    NETIF_STATUS_MEDIA_DISCONNECT;
				spin_unlock_irqrestore(&etdev->Lock,
						       flags);

				/* Only indicate state if we're in loopback
				 * mode
				 */
				if (etdev->RegistryPhyLoopbk == false)
					netif_carrier_off(etdev->netdev);
			}

			etdev->linkspeed = 0;
			etdev->duplex_mode = 0;

			/* Free the packets being actively sent & stopped */
			et131x_free_busy_send_packets(etdev);

			/* Re-initialize the send structures */
			et131x_init_send(etdev);

			/* Reset the RFD list and re-start RU */
			et131x_reset_recv(etdev);

			/*
			 * Bring the device back to the state it was during
			 * init prior to autonegotiation being complete. This
			 * way, when we get the auto-neg complete interrupt,
			 * we can complete init by calling ConfigMacREGS2.
			 */
			et131x_soft_reset(etdev);

			/* Setup ET1310 as per the documentation */
			et131x_adapter_setup(etdev);

			/* Setup the PHY into coma mode until the cable is
			 * plugged back in
			 */
			if (etdev->RegistryPhyComa == 1)
				EnablePhyComa(etdev);
		}
	}

	if (bmsr_ints.bits.auto_neg_complete ||
	    (etdev->AiForceDpx == 3 && bmsr_ints.bits.link_status)) {
		if (bmsr.bits.auto_neg_complete || etdev->AiForceDpx == 3) {
			ET1310_PhyLinkStatus(etdev,
					     &link_status, &autoneg_status,
					     &speed, &duplex, &mdi_mdix,
					     &masterslave, &polarity);

			etdev->linkspeed = speed;
			etdev->duplex_mode = duplex;

			etdev->PoMgmt.TransPhyComaModeOnBoot = 20;

			if (etdev->linkspeed == TRUEPHY_SPEED_10MBPS) {
				/*
				 * NOTE - Is there a way to query this without
				 * TruePHY?
				 * && TRU_QueryCoreType(etdev->hTruePhy, 0)== EMI_TRUEPHY_A13O) {
				 */
				uint16_t Register18;

				MiRead(etdev, 0x12, &Register18);
				MiWrite(etdev, 0x12, Register18 | 0x4);
				MiWrite(etdev, 0x10, Register18 | 0x8402);
				MiWrite(etdev, 0x11, Register18 | 511);
				MiWrite(etdev, 0x12, Register18);
			}

			ConfigFlowControl(etdev);

			if (etdev->linkspeed == TRUEPHY_SPEED_1000MBPS &&
					etdev->RegistryJumboPacket > 2048)
				ET1310_PhyAndOrReg(etdev, 0x16, 0xcfff,
								   0x2000);

			SetRxDmaTimer(etdev);
			ConfigMACRegs2(etdev);
		}
	}
}