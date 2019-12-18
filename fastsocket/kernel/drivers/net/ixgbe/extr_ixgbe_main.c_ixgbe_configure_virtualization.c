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
struct TYPE_5__ {int /*<<< orphan*/  (* set_mac_anti_spoofing ) (struct ixgbe_hw*,int,scalar_t__) ;int /*<<< orphan*/  (* set_vmdq ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_6__ {TYPE_2__ ops; } ;
struct ixgbe_hw {TYPE_3__ mac; } ;
struct ixgbe_adapter {int flags; int antispoofing_enabled; scalar_t__ num_vfs; TYPE_1__* ring_feature; struct ixgbe_hw hw; } ;
struct TYPE_4__ {int mask; } ;

/* Variables and functions */
#define  IXGBE_82599_VMDQ_4Q_MASK 129 
#define  IXGBE_82599_VMDQ_8Q_MASK 128 
 int IXGBE_FLAG_SRIOV_ENABLED ; 
 int /*<<< orphan*/  IXGBE_GCR_EXT ; 
 int IXGBE_GCR_EXT_VT_MODE_16 ; 
 int IXGBE_GCR_EXT_VT_MODE_32 ; 
 int IXGBE_GCR_EXT_VT_MODE_64 ; 
 int /*<<< orphan*/  IXGBE_PFDTXGSWC ; 
 int IXGBE_PFDTXGSWC_VT_LBEN ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_VFRE (int) ; 
 int /*<<< orphan*/  IXGBE_VFTE (int) ; 
 int IXGBE_VMD_CTL_VMDQ_EN ; 
 int /*<<< orphan*/  IXGBE_VT_CTL ; 
 int IXGBE_VT_CTL_POOL_MASK ; 
 int IXGBE_VT_CTL_POOL_SHIFT ; 
 int IXGBE_VT_CTL_REPLEN ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 size_t RING_F_VMDQ ; 
 int VMDQ_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*,int,scalar_t__) ; 

__attribute__((used)) static void ixgbe_configure_virtualization(struct ixgbe_adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;
	u32 reg_offset, vf_shift;
	u32 gcr_ext, vmdctl;

	if (!(adapter->flags & IXGBE_FLAG_SRIOV_ENABLED))
		return;

	vmdctl = IXGBE_READ_REG(hw, IXGBE_VT_CTL);
	vmdctl |= IXGBE_VMD_CTL_VMDQ_EN;
	vmdctl &= ~IXGBE_VT_CTL_POOL_MASK;
	vmdctl |= VMDQ_P(0) << IXGBE_VT_CTL_POOL_SHIFT;
	vmdctl |= IXGBE_VT_CTL_REPLEN;
	IXGBE_WRITE_REG(hw, IXGBE_VT_CTL, vmdctl);

	vf_shift = VMDQ_P(0) % 32;
	reg_offset = (VMDQ_P(0) >= 32) ? 1 : 0;

	/* Enable only the PF's pool for Tx/Rx */
	IXGBE_WRITE_REG(hw, IXGBE_VFRE(reg_offset), (~0) << vf_shift);
	IXGBE_WRITE_REG(hw, IXGBE_VFRE(reg_offset ^ 1), reg_offset - 1);
	IXGBE_WRITE_REG(hw, IXGBE_VFTE(reg_offset), (~0) << vf_shift);
	IXGBE_WRITE_REG(hw, IXGBE_VFTE(reg_offset ^ 1), reg_offset - 1);
	IXGBE_WRITE_REG(hw, IXGBE_PFDTXGSWC, IXGBE_PFDTXGSWC_VT_LBEN);

	/* Map PF MAC address in RAR Entry 0 to first pool following VFs */
	hw->mac.ops.set_vmdq(hw, 0, VMDQ_P(0));

	/*
	 * Set up VF register offsets for selected VT Mode,
	 * i.e. 32 or 64 VFs for SR-IOV
	 */
	switch (adapter->ring_feature[RING_F_VMDQ].mask) {
	case IXGBE_82599_VMDQ_8Q_MASK:
		gcr_ext = IXGBE_GCR_EXT_VT_MODE_16;
		break;
	case IXGBE_82599_VMDQ_4Q_MASK:
		gcr_ext = IXGBE_GCR_EXT_VT_MODE_32;
		break;
	default:
		gcr_ext = IXGBE_GCR_EXT_VT_MODE_64;
		break;
	}

	IXGBE_WRITE_REG(hw, IXGBE_GCR_EXT, gcr_ext);

	/* enable Tx loopback for VF/PF communication */
	IXGBE_WRITE_REG(hw, IXGBE_PFDTXGSWC, IXGBE_PFDTXGSWC_VT_LBEN);

	/* Enable MAC Anti-Spoofing */
	hw->mac.ops.set_mac_anti_spoofing(hw,
					  (adapter->antispoofing_enabled =
					   (adapter->num_vfs != 0)),
					  adapter->num_vfs);
}