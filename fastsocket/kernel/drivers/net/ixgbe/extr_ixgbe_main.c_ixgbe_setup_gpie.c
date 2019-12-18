#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int type; } ;
struct ixgbe_hw {TYPE_2__ mac; } ;
struct ixgbe_adapter {int flags; int flags2; struct ixgbe_hw hw; TYPE_1__* ring_feature; } ;
struct TYPE_3__ {int mask; } ;

/* Variables and functions */
#define  IXGBE_82599_VMDQ_4Q_MASK 132 
#define  IXGBE_82599_VMDQ_8Q_MASK 131 
 int /*<<< orphan*/  IXGBE_EIAM ; 
 int /*<<< orphan*/  IXGBE_EIAM_EX (int) ; 
 int IXGBE_EICS_RTX_QUEUE ; 
 int IXGBE_EIMS_TS ; 
 int IXGBE_FLAG2_TEMP_SENSOR_CAPABLE ; 
 int IXGBE_FLAG_FAN_FAIL_CAPABLE ; 
 int IXGBE_FLAG_MSIX_ENABLED ; 
 int IXGBE_FLAG_SRIOV_ENABLED ; 
 int /*<<< orphan*/  IXGBE_GPIE ; 
 int IXGBE_GPIE_EIAME ; 
 int IXGBE_GPIE_MSIX_MODE ; 
 int IXGBE_GPIE_OCD ; 
 int IXGBE_GPIE_PBA_SUPPORT ; 
 int IXGBE_GPIE_VTMODE_16 ; 
 int IXGBE_GPIE_VTMODE_32 ; 
 int IXGBE_GPIE_VTMODE_64 ; 
 int IXGBE_GPIE_VTMODE_MASK ; 
 int IXGBE_SDP0_GPIEN ; 
 int IXGBE_SDP1_GPIEN ; 
 int IXGBE_SDP2_GPIEN ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 size_t RING_F_VMDQ ; 
#define  ixgbe_mac_82598EB 130 
#define  ixgbe_mac_82599EB 129 
#define  ixgbe_mac_X540 128 

__attribute__((used)) static void ixgbe_setup_gpie(struct ixgbe_adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;
	u32 gpie = 0;

	if (adapter->flags & IXGBE_FLAG_MSIX_ENABLED) {
		gpie = IXGBE_GPIE_MSIX_MODE | IXGBE_GPIE_PBA_SUPPORT |
		       IXGBE_GPIE_OCD;
		gpie |= IXGBE_GPIE_EIAME;
		/*
		 * use EIAM to auto-mask when MSI-X interrupt is asserted
		 * this saves a register write for every interrupt
		 */
		switch (hw->mac.type) {
		case ixgbe_mac_82598EB:
			IXGBE_WRITE_REG(hw, IXGBE_EIAM, IXGBE_EICS_RTX_QUEUE);
			break;
		case ixgbe_mac_82599EB:
		case ixgbe_mac_X540:
		default:
			IXGBE_WRITE_REG(hw, IXGBE_EIAM_EX(0), 0xFFFFFFFF);
			IXGBE_WRITE_REG(hw, IXGBE_EIAM_EX(1), 0xFFFFFFFF);
			break;
		}
	} else {
		/* legacy interrupts, use EIAM to auto-mask when reading EICR,
		 * specifically only auto mask tx and rx interrupts */
		IXGBE_WRITE_REG(hw, IXGBE_EIAM, IXGBE_EICS_RTX_QUEUE);
	}

	/* XXX: to interrupt immediately for EICS writes, enable this */
	/* gpie |= IXGBE_GPIE_EIMEN; */

	if (adapter->flags & IXGBE_FLAG_SRIOV_ENABLED) {
		gpie &= ~IXGBE_GPIE_VTMODE_MASK;

		switch (adapter->ring_feature[RING_F_VMDQ].mask) {
		case IXGBE_82599_VMDQ_8Q_MASK:
			gpie |= IXGBE_GPIE_VTMODE_16;
			break;
		case IXGBE_82599_VMDQ_4Q_MASK:
			gpie |= IXGBE_GPIE_VTMODE_32;
			break;
		default:
			gpie |= IXGBE_GPIE_VTMODE_64;
			break;
		}
	}

	/* Enable Thermal over heat sensor interrupt */
	if (adapter->flags2 & IXGBE_FLAG2_TEMP_SENSOR_CAPABLE) {
		switch (adapter->hw.mac.type) {
		case ixgbe_mac_82599EB:
			gpie |= IXGBE_SDP0_GPIEN;
			break;
		case ixgbe_mac_X540:
			gpie |= IXGBE_EIMS_TS;
			break;
		default:
			break;
		}
	}

	/* Enable fan failure interrupt */
	if (adapter->flags & IXGBE_FLAG_FAN_FAIL_CAPABLE)
		gpie |= IXGBE_SDP1_GPIEN;

	if (hw->mac.type == ixgbe_mac_82599EB) {
		gpie |= IXGBE_SDP1_GPIEN;
		gpie |= IXGBE_SDP2_GPIEN;
	}

	IXGBE_WRITE_REG(hw, IXGBE_GPIE, gpie);
}