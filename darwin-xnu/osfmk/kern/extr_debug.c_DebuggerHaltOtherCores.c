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
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  DebuggerXCallEnter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  mp_kdp_enter (int /*<<< orphan*/ ) ; 

__attribute__((used)) static kern_return_t
DebuggerHaltOtherCores(boolean_t proceed_on_failure)
{
#if CONFIG_EMBEDDED
	return DebuggerXCallEnter(proceed_on_failure);
#else /* CONFIG_EMBEDDED */
#pragma unused(proceed_on_failure)
	mp_kdp_enter(proceed_on_failure);
	return KERN_SUCCESS;
#endif
}