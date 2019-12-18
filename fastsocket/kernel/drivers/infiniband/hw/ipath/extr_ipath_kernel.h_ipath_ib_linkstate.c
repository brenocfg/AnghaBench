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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct ipath_devdata {int ibcs_ls_shift; } ;

/* Variables and functions */
 scalar_t__ INFINIPATH_IBCS_LINKSTATE_MASK ; 
 scalar_t__ INFINIPATH_IBCS_L_STATE_ACTIVE ; 
 scalar_t__ INFINIPATH_IBCS_L_STATE_ACT_DEFER ; 

__attribute__((used)) static inline u32 ipath_ib_linkstate(struct ipath_devdata *dd, u64 ibcs)
{
	u32 state = (u32)(ibcs >> dd->ibcs_ls_shift) &
		INFINIPATH_IBCS_LINKSTATE_MASK;
	if (state == INFINIPATH_IBCS_L_STATE_ACT_DEFER)
		state = INFINIPATH_IBCS_L_STATE_ACTIVE;
	return state;
}