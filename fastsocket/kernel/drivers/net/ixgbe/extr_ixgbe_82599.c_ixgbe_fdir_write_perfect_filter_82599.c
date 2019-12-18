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
struct TYPE_2__ {int bkt_hash; int flow_type; scalar_t__ vm_pool; int /*<<< orphan*/  vlan_id; int /*<<< orphan*/  flex_bytes; int /*<<< orphan*/  src_port; int /*<<< orphan*/  dst_port; int /*<<< orphan*/ * dst_ip; int /*<<< orphan*/ * src_ip; } ;
union ixgbe_atr_input {TYPE_1__ formatted; } ;
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct ixgbe_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_FDIRCMD ; 
 int IXGBE_FDIRCMD_CMD_ADD_FLOW ; 
 int IXGBE_FDIRCMD_DROP ; 
 int IXGBE_FDIRCMD_FILTER_UPDATE ; 
 int IXGBE_FDIRCMD_FLOW_TYPE_SHIFT ; 
 int IXGBE_FDIRCMD_LAST ; 
 int IXGBE_FDIRCMD_QUEUE_EN ; 
 int IXGBE_FDIRCMD_RX_QUEUE_SHIFT ; 
 int IXGBE_FDIRCMD_VT_POOL_SHIFT ; 
 int /*<<< orphan*/  IXGBE_FDIRHASH ; 
 int IXGBE_FDIRHASH_SIG_SW_INDEX_SHIFT ; 
 int /*<<< orphan*/  IXGBE_FDIRIPDA ; 
 int /*<<< orphan*/  IXGBE_FDIRIPSA ; 
 int /*<<< orphan*/  IXGBE_FDIRPORT ; 
 int IXGBE_FDIRPORT_DESTINATION_SHIFT ; 
 int /*<<< orphan*/  IXGBE_FDIRSIPv6 (int) ; 
 int /*<<< orphan*/  IXGBE_FDIRVLAN ; 
 int IXGBE_FDIRVLAN_FLEX_SHIFT ; 
 scalar_t__ IXGBE_FDIR_DROP_QUEUE ; 
 int IXGBE_STORE_AS_BE16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WRITE_FLUSH (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG_BE32 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 

s32 ixgbe_fdir_write_perfect_filter_82599(struct ixgbe_hw *hw,
					  union ixgbe_atr_input *input,
					  u16 soft_id, u8 queue)
{
	u32 fdirport, fdirvlan, fdirhash, fdircmd;

	/* currently IPv6 is not supported, must be programmed with 0 */
	IXGBE_WRITE_REG_BE32(hw, IXGBE_FDIRSIPv6(0),
			     input->formatted.src_ip[0]);
	IXGBE_WRITE_REG_BE32(hw, IXGBE_FDIRSIPv6(1),
			     input->formatted.src_ip[1]);
	IXGBE_WRITE_REG_BE32(hw, IXGBE_FDIRSIPv6(2),
			     input->formatted.src_ip[2]);

	/* record the source address (big-endian) */
	IXGBE_WRITE_REG_BE32(hw, IXGBE_FDIRIPSA, input->formatted.src_ip[0]);

	/* record the first 32 bits of the destination address (big-endian) */
	IXGBE_WRITE_REG_BE32(hw, IXGBE_FDIRIPDA, input->formatted.dst_ip[0]);

	/* record source and destination port (little-endian)*/
	fdirport = ntohs(input->formatted.dst_port);
	fdirport <<= IXGBE_FDIRPORT_DESTINATION_SHIFT;
	fdirport |= ntohs(input->formatted.src_port);
	IXGBE_WRITE_REG(hw, IXGBE_FDIRPORT, fdirport);

	/* record vlan (little-endian) and flex_bytes(big-endian) */
	fdirvlan = IXGBE_STORE_AS_BE16(input->formatted.flex_bytes);
	fdirvlan <<= IXGBE_FDIRVLAN_FLEX_SHIFT;
	fdirvlan |= ntohs(input->formatted.vlan_id);
	IXGBE_WRITE_REG(hw, IXGBE_FDIRVLAN, fdirvlan);

	/* configure FDIRHASH register */
	fdirhash = input->formatted.bkt_hash;
	fdirhash |= soft_id << IXGBE_FDIRHASH_SIG_SW_INDEX_SHIFT;
	IXGBE_WRITE_REG(hw, IXGBE_FDIRHASH, fdirhash);

	/*
	 * flush all previous writes to make certain registers are
	 * programmed prior to issuing the command
	 */
	IXGBE_WRITE_FLUSH(hw);

	/* configure FDIRCMD register */
	fdircmd = IXGBE_FDIRCMD_CMD_ADD_FLOW | IXGBE_FDIRCMD_FILTER_UPDATE |
		  IXGBE_FDIRCMD_LAST | IXGBE_FDIRCMD_QUEUE_EN;
	if (queue == IXGBE_FDIR_DROP_QUEUE)
		fdircmd |= IXGBE_FDIRCMD_DROP;
	fdircmd |= input->formatted.flow_type << IXGBE_FDIRCMD_FLOW_TYPE_SHIFT;
	fdircmd |= (u32)queue << IXGBE_FDIRCMD_RX_QUEUE_SHIFT;
	fdircmd |= (u32)input->formatted.vm_pool << IXGBE_FDIRCMD_VT_POOL_SHIFT;

	IXGBE_WRITE_REG(hw, IXGBE_FDIRCMD, fdircmd);

	return 0;
}