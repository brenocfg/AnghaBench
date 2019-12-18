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
typedef  int /*<<< orphan*/  atf_list_t ;
typedef  int /*<<< orphan*/  atf_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  append_arg1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_no_error () ; 
 int /*<<< orphan*/  strdup (char const* const) ; 

__attribute__((used)) static
atf_error_t
append_optargs(const char *const optargs[], atf_list_t *argv)
{
    atf_error_t err;

    err = atf_no_error();
    while (*optargs != NULL && !atf_is_error(err)) {
        err = append_arg1(strdup(*optargs), argv);
        optargs++;
    }

    return err;
}