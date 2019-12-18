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
struct file {int f_mode; struct socket* private_data; int /*<<< orphan*/ * f_op; } ;

/* Variables and functions */
 int ENOTSOCK ; 
 int FMODE_FASTSOCKET ; 
 int /*<<< orphan*/  socket_file_ops ; 

__attribute__((used)) static struct socket *sock_from_file(struct file *file, int *err)
{
	if (file->f_mode & FMODE_FASTSOCKET || file->f_op == &socket_file_ops)
		return file->private_data;	/* set in sock_map_fd */

	*err = -ENOTSOCK;
	return NULL;
}