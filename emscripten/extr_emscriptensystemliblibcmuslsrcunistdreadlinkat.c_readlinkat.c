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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_readlinkat ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ,int,char const*,char*,size_t) ; 

ssize_t readlinkat(int fd, const char *restrict path, char *restrict buf, size_t bufsize)
{
	return syscall(SYS_readlinkat, fd, path, buf, bufsize);
}