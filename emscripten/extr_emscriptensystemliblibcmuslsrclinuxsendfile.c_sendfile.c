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
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_sendfile ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,size_t) ; 

ssize_t sendfile(int out_fd, int in_fd, off_t *ofs, size_t count)
{
	return syscall(SYS_sendfile, out_fd, in_fd, ofs, count);
}