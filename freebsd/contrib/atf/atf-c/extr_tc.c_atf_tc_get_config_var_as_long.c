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
typedef  int /*<<< orphan*/  atf_tc_t ;
typedef  int /*<<< orphan*/  atf_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  atf_error_free (int /*<<< orphan*/ ) ; 
 scalar_t__ atf_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_tc_fail (char*,char const*,char const*) ; 
 char* atf_tc_get_config_var (int /*<<< orphan*/  const*,char const*) ; 
 int /*<<< orphan*/  atf_text_to_long (char const*,long*) ; 

long
atf_tc_get_config_var_as_long(const atf_tc_t *tc, const char *name)
{
    long val;
    const char *strval;
    atf_error_t err;

    strval = atf_tc_get_config_var(tc, name);
    err = atf_text_to_long(strval, &val);
    if (atf_is_error(err)) {
        atf_error_free(err);
        atf_tc_fail("Configuration variable %s does not have a valid "
                    "long value; found %s", name, strval);
    }

    return val;
}