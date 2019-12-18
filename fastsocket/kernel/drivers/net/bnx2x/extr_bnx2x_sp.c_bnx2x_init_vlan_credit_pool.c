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
typedef  int u8 ;
struct bnx2x_credit_pool_obj {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E1x (struct bnx2x*) ; 
 int MAX_VLAN_CREDIT_E2 ; 
 int /*<<< orphan*/  bnx2x_init_credit_pool (struct bnx2x_credit_pool_obj*,int,int) ; 

void bnx2x_init_vlan_credit_pool(struct bnx2x *bp,
				 struct bnx2x_credit_pool_obj *p,
				 u8 func_id,
				 u8 func_num)
{
	if (CHIP_IS_E1x(bp)) {
		/* There is no VLAN credit in HW on 57710 and 57711 only
		 * MAC / MAC-VLAN can be set
		 */
		bnx2x_init_credit_pool(p, 0, -1);
	} else {
		/* CAM credit is equally divided between all active functions
		 * on the PATH.
		 */
		if (func_num > 0) {
			int credit = MAX_VLAN_CREDIT_E2 / func_num;
			bnx2x_init_credit_pool(p, func_id * credit, credit);
		} else
			/* this should never happen! Block VLAN operations. */
			bnx2x_init_credit_pool(p, 0, 0);
	}
}