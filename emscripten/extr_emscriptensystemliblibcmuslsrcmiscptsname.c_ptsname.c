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
 int __ptsname_r (int,char*,int) ; 
 int errno ; 

char *ptsname(int fd)
{
	static char buf[9 + sizeof(int)*3 + 1];
	int err = __ptsname_r(fd, buf, sizeof buf);
	if (err) {
		errno = err;
		return 0;
	}
	return buf;
}