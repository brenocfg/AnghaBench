#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct socket {TYPE_2__* sk; TYPE_1__* ops; } ;
struct file {scalar_t__ private_data; struct file* sub_file; } ;
struct TYPE_4__ {int sk_max_ack_backlog; } ;
struct TYPE_3__ {int (* listen ) (struct socket*,int) ;} ;

/* Variables and functions */
 int EBADF ; 
 int stub1 (struct socket*,int) ; 
 int stub2 (struct socket*,int) ; 

int fsocket_listen(struct file *file, int backlog)
{
	struct socket *sock, *lsock;
	struct file *sfile;
	int ret = 0;
	int old_backlog;

	sock = (struct socket *)file->private_data;
	if (sock) {
		ret = sock->ops->listen(sock, backlog);
		if (ret < 0)
			goto out;
	} else {
		ret = -EBADF;
		goto out;
	}

	sfile = file->sub_file;
	if (sfile) {
		old_backlog = sock->sk->sk_max_ack_backlog;
		lsock = (struct socket *)file->private_data;
		if (lsock) {
			ret = sock->ops->listen(lsock, backlog);
			if (ret < 0)
				goto restore_out;
		} else {
			ret = -EBADF;
			goto restore_out;
		}
	}

	goto out;

restore_out:
	sock->sk->sk_max_ack_backlog = old_backlog;
out:
	return ret;
}