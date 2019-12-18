#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct socket {TYPE_1__* ops; int /*<<< orphan*/  sk; } ;
struct pipe_inode_info {int dummy; } ;
struct file {struct socket* private_data; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* splice_read ) (struct socket*,int /*<<< orphan*/ *,struct pipe_inode_info*,size_t,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  sock_update_classid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct socket*,int /*<<< orphan*/ *,struct pipe_inode_info*,size_t,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

ssize_t sock_splice_read(struct file *file, loff_t *ppos,
			        struct pipe_inode_info *pipe, size_t len,
				unsigned int flags)
{
	struct socket *sock = file->private_data;

	if (unlikely(!sock->ops->splice_read))
		return -EINVAL;

	sock_update_classid(sock->sk);

	return sock->ops->splice_read(sock, ppos, pipe, len, flags);
}