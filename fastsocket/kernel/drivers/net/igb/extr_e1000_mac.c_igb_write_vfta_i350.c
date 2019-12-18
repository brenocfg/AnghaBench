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
typedef  int /*<<< orphan*/  u32 ;
struct e1000_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_VFTA ; 
 int /*<<< orphan*/  array_wr32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrfl () ; 

__attribute__((used)) static void igb_write_vfta_i350(struct e1000_hw *hw, u32 offset, u32 value)
{
	int i;

	for (i = 0; i < 10; i++)
		array_wr32(E1000_VFTA, offset, value);

	wrfl();
}