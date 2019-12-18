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
typedef  int u32 ;
struct ixgb_hw {int dummy; } ;

/* Variables and functions */
 int IXGB_READ_REG_ARRAY (struct ixgb_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IXGB_WRITE_REG_ARRAY (struct ixgb_hw*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  MTA ; 

__attribute__((used)) static void
ixgb_mta_set(struct ixgb_hw *hw,
		  u32 hash_value)
{
	u32 hash_bit, hash_reg;
	u32 mta_reg;

	/* The MTA is a register array of 128 32-bit registers.
	 * It is treated like an array of 4096 bits.  We want to set
	 * bit BitArray[hash_value]. So we figure out what register
	 * the bit is in, read it, OR in the new bit, then write
	 * back the new value.  The register is determined by the
	 * upper 7 bits of the hash value and the bit within that
	 * register are determined by the lower 5 bits of the value.
	 */
	hash_reg = (hash_value >> 5) & 0x7F;
	hash_bit = hash_value & 0x1F;

	mta_reg = IXGB_READ_REG_ARRAY(hw, MTA, hash_reg);

	mta_reg |= (1 << hash_bit);

	IXGB_WRITE_REG_ARRAY(hw, MTA, hash_reg, mta_reg);

	return;
}