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
 int /*<<< orphan*/  a_barrier () ; 
 int /*<<< orphan*/  aio_cancel (int,int /*<<< orphan*/ ) ; 
 scalar_t__ aio_fd_cnt ; 

int __aio_close(int fd)
{
	a_barrier();
	if (aio_fd_cnt) aio_cancel(fd, 0);
	return fd;
}