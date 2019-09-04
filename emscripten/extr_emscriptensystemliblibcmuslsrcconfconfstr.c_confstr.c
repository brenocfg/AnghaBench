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
 int _CS_POSIX_V6_ILP32_OFF32_CFLAGS ; 
 int /*<<< orphan*/  errno ; 
 size_t snprintf (char*,size_t,char*,char const*) ; 

size_t confstr(int name, char *buf, size_t len)
{
	const char *s = "";
	if (!name) {
		s = "/bin:/usr/bin";
	} else if ((name&~4U)!=1 && name-_CS_POSIX_V6_ILP32_OFF32_CFLAGS>31U) {
		errno = EINVAL;
		return 0;
	}
	// snprintf is overkill but avoid wasting code size to implement
	// this completely useless function and its truncation semantics
	return snprintf(buf, len, "%s", s) + 1;
}