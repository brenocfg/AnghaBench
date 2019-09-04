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
struct stat {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_fstatat ; 
 int syscall (int /*<<< orphan*/ ,int,char const*,struct stat*,int) ; 

int fstatat(int fd, const char *restrict path, struct stat *restrict buf, int flag)
{
	return syscall(SYS_fstatat, fd, path, buf, flag);
}