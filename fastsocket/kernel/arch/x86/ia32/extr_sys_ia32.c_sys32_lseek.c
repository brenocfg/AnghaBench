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
 long sys_lseek (unsigned int,int,unsigned int) ; 

long sys32_lseek(unsigned int fd, int offset, unsigned int whence)
{
	return sys_lseek(fd, offset, whence);
}