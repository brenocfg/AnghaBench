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
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  T_ASSERT_MACH_SUCCESS (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  T_LOG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int /*<<< orphan*/  _original ; 
 int /*<<< orphan*/  host_get_atm_diagnostic_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mach_host_self () ; 

__attribute__((used)) static uint32_t
_save_atm_diagnostic_flag(void)
{
    kern_return_t kr;
    kr = host_get_atm_diagnostic_flag(mach_host_self(), &_original);
    T_QUIET; T_ASSERT_MACH_SUCCESS(kr, "host_get_atm_diagnostic_flag()");
    T_LOG("Original ATM diagnostic flag: 0x%08x", _original);
    return _original;
}