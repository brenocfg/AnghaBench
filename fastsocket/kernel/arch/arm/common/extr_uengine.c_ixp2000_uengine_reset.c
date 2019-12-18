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

/* Variables and functions */
 int /*<<< orphan*/  IXP_RESET1 ; 
 int ixp2000_reg_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixp2000_reg_wrb (int /*<<< orphan*/ ,int) ; 
 int ixp2000_uengine_mask ; 

void ixp2000_uengine_reset(u32 uengine_mask)
{
	u32 value;

	value = ixp2000_reg_read(IXP_RESET1) & ~ixp2000_uengine_mask;

	uengine_mask &= ixp2000_uengine_mask;
	ixp2000_reg_wrb(IXP_RESET1, value | uengine_mask);
	ixp2000_reg_wrb(IXP_RESET1, value);
}