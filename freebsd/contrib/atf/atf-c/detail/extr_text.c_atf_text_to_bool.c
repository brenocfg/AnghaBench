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
typedef  int /*<<< orphan*/  atf_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  atf_libc_error (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  atf_no_error () ; 
 scalar_t__ strcasecmp (char const*,char*) ; 

atf_error_t
atf_text_to_bool(const char *str, bool *b)
{
    atf_error_t err;

    if (strcasecmp(str, "yes") == 0 ||
        strcasecmp(str, "true") == 0) {
        *b = true;
        err = atf_no_error();
    } else if (strcasecmp(str, "no") == 0 ||
               strcasecmp(str, "false") == 0) {
        *b = false;
        err = atf_no_error();
    } else {
        /* XXX Not really a libc error. */
        err = atf_libc_error(EINVAL, "Cannot convert string '%s' "
                             "to boolean", str);
    }

    return err;
}