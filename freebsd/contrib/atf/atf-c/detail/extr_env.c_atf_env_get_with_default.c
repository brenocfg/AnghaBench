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
 char* getenv (char const*) ; 

const char *
atf_env_get_with_default(const char *name, const char *default_value)
{
    const char* val = getenv(name);
    if (val == NULL)
        return default_value;
    else
        return val;
}