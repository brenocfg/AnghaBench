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
 int /*<<< orphan*/  KENV_SET ; 
 int kenv (int /*<<< orphan*/ ,char const*,char*,scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,char const*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int
ksetenv(const char *env, char *val)
{
	int ret;

	ret = kenv(KENV_SET, env, val, strlen(val) + 1);
	if (ret == 0)
		printf("%s=\"%s\"\n", env, val);
	return (ret);
}