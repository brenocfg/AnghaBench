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

/* Variables and functions */
 long atf_tc_get_config_var_as_long (int /*<<< orphan*/  const*,char const*) ; 
 int /*<<< orphan*/  atf_tc_has_config_var (int /*<<< orphan*/  const*,char const*) ; 

long
atf_tc_get_config_var_as_long_wd(const atf_tc_t *tc, const char *name,
                                 const long defval)
{
    long val;

    if (!atf_tc_has_config_var(tc, name))
        val = defval;
    else
        val = atf_tc_get_config_var_as_long(tc, name);

    return val;
}