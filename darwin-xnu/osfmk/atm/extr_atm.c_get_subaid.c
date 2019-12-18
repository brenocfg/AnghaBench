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
typedef  scalar_t__ mach_atm_subaid_t ;
typedef  int /*<<< orphan*/  SInt64 ;

/* Variables and functions */
 scalar_t__ OSIncrementAtomic64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  global_subaid ; 

__attribute__((used)) static mach_atm_subaid_t
get_subaid()
{
	mach_atm_subaid_t next_subaid;
	next_subaid = (mach_atm_subaid_t)OSIncrementAtomic64((SInt64 *)&global_subaid);
	return next_subaid;
}