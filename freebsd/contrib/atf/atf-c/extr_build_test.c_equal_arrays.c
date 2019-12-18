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
 scalar_t__ strcmp (char const* const,char*) ; 

__attribute__((used)) static
bool
equal_arrays(const char *const *exp_array, char **actual_array)
{
    bool equal;

    if (*exp_array == NULL && *actual_array == NULL)
        equal = true;
    else if (*exp_array == NULL || *actual_array == NULL)
        equal = false;
    else {
        equal = true;
        while (*actual_array != NULL) {
            if (*exp_array == NULL || strcmp(*exp_array, *actual_array) != 0) {
                equal = false;
                break;
            }
            exp_array++;
            actual_array++;
        }
    }

    return equal;
}