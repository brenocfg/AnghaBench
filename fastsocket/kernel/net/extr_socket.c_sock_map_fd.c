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
struct socket {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fd_install (int,struct file*) ; 
 scalar_t__ likely (int) ; 
 int sock_alloc_file (struct socket*,struct file**,int) ; 

int sock_map_fd(struct socket *sock, int flags)
{
	struct file *newfile;
	int fd = sock_alloc_file(sock, &newfile, flags);

	if (likely(fd >= 0))
		fd_install(fd, newfile);

	return fd;
}