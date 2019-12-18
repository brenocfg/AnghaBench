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

/* Variables and functions */
 int CPUMF_LCCTL_ACTCTL_SHIFT ; 
 int* cpumf_state_ctl ; 

__attribute__((used)) static void ctr_set_stop(u64 *state, int ctr_set)
{
	*state &= ~(cpumf_state_ctl[ctr_set] << CPUMF_LCCTL_ACTCTL_SHIFT);
}