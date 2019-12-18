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
 int /*<<< orphan*/  RE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_env_set (char const*,char const*) ; 
 int /*<<< orphan*/  printf (char*,char const*,char const*) ; 

__attribute__((used)) static
void
verbose_set_env(const char *var, const char *val)
{
    printf("Setting %s to '%s'\n", var, val);
    RE(atf_env_set(var, val));
}