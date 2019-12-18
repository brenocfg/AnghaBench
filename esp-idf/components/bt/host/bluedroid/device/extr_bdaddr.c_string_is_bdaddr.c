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
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ets_isxdigit (char const) ; 
 size_t strlen (char const*) ; 

bool string_is_bdaddr(const char *string)
{
    assert(string != NULL);

    size_t len = strlen(string);
    if (len != 17) {
        return false;
    }

    for (size_t i = 0; i < len; ++i) {
        // Every 3rd char must be ':'.
        if (((i + 1) % 3) == 0 && string[i] != ':') {
            return false;
        }

        // All other chars must be a hex digit.
        if (((i + 1) % 3) != 0 && !ets_isxdigit(string[i])) {
            return false;
        }
    }
    return true;
}