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
 int /*<<< orphan*/  FTW_PHYS ; 
 int nftw (char const*,int (*) (),int,int /*<<< orphan*/ ) ; 

int ftw(const char *path, int (*fn)(const char *, const struct stat *, int), int fd_limit)
{
	/* The following cast assumes that calling a function with one
	 * argument more than it needs behaves as expected. This is
	 * actually undefined, but works on all real-world machines. */
	return nftw(path, (int (*)())fn, fd_limit, FTW_PHYS);
}