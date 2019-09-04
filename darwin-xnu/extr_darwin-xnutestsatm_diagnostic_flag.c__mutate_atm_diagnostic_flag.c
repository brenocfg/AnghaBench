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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  T_LOG (char*,int /*<<< orphan*/ ) ; 
 int _needs_reset ; 
 scalar_t__ host_set_atm_diagnostic_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mach_host_self () ; 

__attribute__((used)) static kern_return_t
_mutate_atm_diagnostic_flag(uint32_t v)
{
    T_LOG("Try to set ATM diagnostic flag to: 0x%08x", v);
    kern_return_t kr = host_set_atm_diagnostic_flag(mach_host_self(), v);
    if (kr == KERN_SUCCESS) _needs_reset = true;
    return kr;
}