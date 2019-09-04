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
 scalar_t__ EEXIST ; 
 scalar_t__ EINVAL ; 
 int O_ACCMODE ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_RDWR ; 
 int /*<<< orphan*/  __randname (char*) ; 
 scalar_t__ errno ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int open (char*,int,int) ; 
 size_t strlen (char*) ; 

int __mkostemps(char *template, int len, int flags)
{
	size_t l = strlen(template);
	if (l<6 || len>l-6 || memcmp(template+l-len-6, "XXXXXX", 6)) {
		errno = EINVAL;
		return -1;
	}

	flags -= flags & O_ACCMODE;
	int fd, retries = 100;
	do {
		__randname(template+l-len-6);
		if ((fd = open(template, flags | O_RDWR | O_CREAT | O_EXCL, 0600))>=0)
			return fd;
	} while (--retries && errno == EEXIST);

	memcpy(template+l-len-6, "XXXXXX", 6);
	return -1;
}