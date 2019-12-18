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
struct e1000_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_BLK_PHY_RESET ; 
 int E1000_MANC_BLK_PHY_RST_ON_IDE ; 
 int /*<<< orphan*/  MANC ; 
 int er32 (int /*<<< orphan*/ ) ; 

s32 e1000e_check_reset_block_generic(struct e1000_hw *hw)
{
	u32 manc;

	manc = er32(MANC);

	return (manc & E1000_MANC_BLK_PHY_RST_ON_IDE) ? E1000_BLK_PHY_RESET : 0;
}