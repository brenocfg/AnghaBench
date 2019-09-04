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
 int /*<<< orphan*/  EINVAL ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  SYS_getcwd ; 
 int /*<<< orphan*/  errno ; 
 char* strdup (char*) ; 
 scalar_t__ syscall (int /*<<< orphan*/ ,char*,size_t) ; 

char *getcwd(char *buf, size_t size)
{
	char tmp[PATH_MAX];
	if (!buf) {
		buf = tmp;
		size = PATH_MAX;
	} else if (!size) {
		errno = EINVAL;
		return 0;
	}
	if (syscall(SYS_getcwd, buf, size) < 0) return 0;
	return buf == tmp ? strdup(buf) : buf;
}