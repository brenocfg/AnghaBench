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
struct TYPE_2__ {int vm_pool; int flow_type; int flex_bytes; int /*<<< orphan*/ * dst_ip; int /*<<< orphan*/ * src_ip; int /*<<< orphan*/  vlan_id; int /*<<< orphan*/  src_port; int /*<<< orphan*/  dst_port; scalar_t__ bkt_hash; } ;
union ixgbe_atr_input {TYPE_1__ formatted; } ;
typedef  int /*<<< orphan*/  u32 ;
struct ixgbe_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
#define  IXGBE_ATR_L4TYPE_MASK 128 
 int /*<<< orphan*/  IXGBE_ERR_CONFIG ; 
 int /*<<< orphan*/  IXGBE_FDIRDIP4M ; 
 int /*<<< orphan*/  IXGBE_FDIRM ; 
 int /*<<< orphan*/  IXGBE_FDIRM_DIPv6 ; 
 int /*<<< orphan*/  IXGBE_FDIRM_FLEX ; 
 int /*<<< orphan*/  IXGBE_FDIRM_L4P ; 
 int /*<<< orphan*/  IXGBE_FDIRM_POOL ; 
 int /*<<< orphan*/  IXGBE_FDIRM_VLANID ; 
 int /*<<< orphan*/  IXGBE_FDIRM_VLANP ; 
 int /*<<< orphan*/  IXGBE_FDIRSIP4M ; 
 int /*<<< orphan*/  IXGBE_FDIRTCPM ; 
 int /*<<< orphan*/  IXGBE_FDIRUDPM ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG_BE32 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_dbg (struct ixgbe_hw*,char*) ; 
 int /*<<< orphan*/  ixgbe_get_fdirtcpm_82599 (union ixgbe_atr_input*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 

s32 ixgbe_fdir_set_input_mask_82599(struct ixgbe_hw *hw,
				    union ixgbe_atr_input *input_mask)
{
	/* mask IPv6 since it is currently not supported */
	u32 fdirm = IXGBE_FDIRM_DIPv6;
	u32 fdirtcpm;

	/*
	 * Program the relevant mask registers.  If src/dst_port or src/dst_addr
	 * are zero, then assume a full mask for that field.  Also assume that
	 * a VLAN of 0 is unspecified, so mask that out as well.  L4type
	 * cannot be masked out in this implementation.
	 *
	 * This also assumes IPv4 only.  IPv6 masking isn't supported at this
	 * point in time.
	 */

	/* verify bucket hash is cleared on hash generation */
	if (input_mask->formatted.bkt_hash)
		hw_dbg(hw, " bucket hash should always be 0 in mask\n");

	/* Program FDIRM and verify partial masks */
	switch (input_mask->formatted.vm_pool & 0x7F) {
	case 0x0:
		fdirm |= IXGBE_FDIRM_POOL;
	case 0x7F:
		break;
	default:
		hw_dbg(hw, " Error on vm pool mask\n");
		return IXGBE_ERR_CONFIG;
	}

	switch (input_mask->formatted.flow_type & IXGBE_ATR_L4TYPE_MASK) {
	case 0x0:
		fdirm |= IXGBE_FDIRM_L4P;
		if (input_mask->formatted.dst_port ||
		    input_mask->formatted.src_port) {
			hw_dbg(hw, " Error on src/dst port mask\n");
			return IXGBE_ERR_CONFIG;
		}
	case IXGBE_ATR_L4TYPE_MASK:
		break;
	default:
		hw_dbg(hw, " Error on flow type mask\n");
		return IXGBE_ERR_CONFIG;
	}

	switch (ntohs(input_mask->formatted.vlan_id) & 0xEFFF) {
	case 0x0000:
		/* mask VLAN ID, fall through to mask VLAN priority */
		fdirm |= IXGBE_FDIRM_VLANID;
	case 0x0FFF:
		/* mask VLAN priority */
		fdirm |= IXGBE_FDIRM_VLANP;
		break;
	case 0xE000:
		/* mask VLAN ID only, fall through */
		fdirm |= IXGBE_FDIRM_VLANID;
	case 0xEFFF:
		/* no VLAN fields masked */
		break;
	default:
		hw_dbg(hw, " Error on VLAN mask\n");
		return IXGBE_ERR_CONFIG;
	}

	switch (input_mask->formatted.flex_bytes & 0xFFFF) {
	case 0x0000:
		/* Mask Flex Bytes, fall through */
		fdirm |= IXGBE_FDIRM_FLEX;
	case 0xFFFF:
		break;
	default:
		hw_dbg(hw, " Error on flexible byte mask\n");
		return IXGBE_ERR_CONFIG;
	}

	/* Now mask VM pool and destination IPv6 - bits 5 and 2 */
	IXGBE_WRITE_REG(hw, IXGBE_FDIRM, fdirm);

	/* store the TCP/UDP port masks, bit reversed from port layout */
	fdirtcpm = ixgbe_get_fdirtcpm_82599(input_mask);

	/* write both the same so that UDP and TCP use the same mask */
	IXGBE_WRITE_REG(hw, IXGBE_FDIRTCPM, ~fdirtcpm);
	IXGBE_WRITE_REG(hw, IXGBE_FDIRUDPM, ~fdirtcpm);

	/* store source and destination IP masks (big-enian) */
	IXGBE_WRITE_REG_BE32(hw, IXGBE_FDIRSIP4M,
			     ~input_mask->formatted.src_ip[0]);
	IXGBE_WRITE_REG_BE32(hw, IXGBE_FDIRDIP4M,
			     ~input_mask->formatted.dst_ip[0]);

	return 0;
}