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
 int /*<<< orphan*/  SEEK_SET ; 
 int errno ; 
 unsigned long long lseek64 (int,unsigned long long,int /*<<< orphan*/ ) ; 

int os_seek_file(int fd, unsigned long long offset)
{
	unsigned long long actual;

	actual = lseek64(fd, offset, SEEK_SET);
	if (actual != offset)
		return -errno;
	return 0;
}