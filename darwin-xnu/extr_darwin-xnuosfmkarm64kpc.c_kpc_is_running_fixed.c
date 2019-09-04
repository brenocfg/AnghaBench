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
typedef  int boolean_t ;

/* Variables and functions */
 int KPC_CLASS_FIXED_MASK ; 
 int kpc_running_classes ; 

boolean_t
kpc_is_running_fixed(void)
{
	return (kpc_running_classes & KPC_CLASS_FIXED_MASK) == KPC_CLASS_FIXED_MASK;
}