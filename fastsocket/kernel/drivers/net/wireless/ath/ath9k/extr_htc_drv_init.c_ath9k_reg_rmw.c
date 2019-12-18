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

/* Variables and functions */
 int /*<<< orphan*/  ath9k_regread (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_regwrite (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 ath9k_reg_rmw(void *hw_priv, u32 reg_offset, u32 set, u32 clr)
{
	u32 val;

	val = ath9k_regread(hw_priv, reg_offset);
	val &= ~clr;
	val |= set;
	ath9k_regwrite(hw_priv, val, reg_offset);
	return val;
}