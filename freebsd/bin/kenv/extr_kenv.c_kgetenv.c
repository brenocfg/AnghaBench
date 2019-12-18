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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  KENV_GET ; 
 int kenv (int /*<<< orphan*/ ,char const*,char*,int) ; 
 int /*<<< orphan*/  printf (char*,char const*,...) ; 
 scalar_t__ vflag ; 

__attribute__((used)) static int
kgetenv(const char *env)
{
	char buf[1024];
	int ret;

	ret = kenv(KENV_GET, env, buf, sizeof(buf));
	if (ret == -1)
		return (ret);
	if (vflag)
		printf("%s=\"%s\"\n", env, buf);
	else
		printf("%s\n", buf);
	return (0);
}