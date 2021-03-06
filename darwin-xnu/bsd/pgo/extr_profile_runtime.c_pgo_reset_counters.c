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
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  OSKextResetPgoCountersLock () ; 
 int /*<<< orphan*/  OSKextResetPgoCountersUnlock () ; 
 int kdp_pgo_reset_counters ; 
 int /*<<< orphan*/  kextpgo_trap () ; 
 int /*<<< orphan*/  ml_set_interrupts_enabled (int /*<<< orphan*/ ) ; 

__attribute__((used)) static kern_return_t
pgo_reset_counters()
{
    kern_return_t r;
    boolean_t istate;

    OSKextResetPgoCountersLock();

    istate = ml_set_interrupts_enabled(FALSE);

    kdp_pgo_reset_counters = 1;
    r = kextpgo_trap();

    ml_set_interrupts_enabled(istate);

    OSKextResetPgoCountersUnlock();
    return r;
}