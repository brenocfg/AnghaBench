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

/* Variables and functions */
 int /*<<< orphan*/  atf_tc_fail_nonfatal (char*) ; 
 int /*<<< orphan*/  equal_arrays (char const* const*,char**) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static
void
check_equal_array(const char *const *exp_array, char **actual_array)
{
    {
        const char *const *exp_ptr;
        printf("Expected arguments:");
        for (exp_ptr = exp_array; *exp_ptr != NULL; exp_ptr++)
            printf(" '%s'", *exp_ptr);
        printf("\n");
    }

    {
        char **actual_ptr;
        printf("Returned arguments:");
        for (actual_ptr = actual_array; *actual_ptr != NULL; actual_ptr++)
            printf(" '%s'", *actual_ptr);
        printf("\n");
    }

    if (!equal_arrays(exp_array, actual_array))
        atf_tc_fail_nonfatal("The constructed argv differs from the "
                             "expected values");
}