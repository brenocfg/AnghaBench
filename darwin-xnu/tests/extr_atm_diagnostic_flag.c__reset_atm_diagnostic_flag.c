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
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  T_ASSERT_FAIL (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_LOG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _needs_reset ; 
 int /*<<< orphan*/  _original ; 
 scalar_t__ host_set_atm_diagnostic_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mach_error_string (scalar_t__) ; 
 int /*<<< orphan*/  mach_host_self () ; 

__attribute__((used)) static void
_reset_atm_diagnostic_flag(void)
{
    if (!_needs_reset) return;
    T_LOG("Reset ATM diagnostic flag to: 0x%08x", _original);
    kern_return_t kr;
    kr = host_set_atm_diagnostic_flag(mach_host_self(), _original);
    if (kr != KERN_SUCCESS) {
        T_ASSERT_FAIL("host_set_atm_diagnostic_flag() failed: %s",
                mach_error_string(kr));
    }
}