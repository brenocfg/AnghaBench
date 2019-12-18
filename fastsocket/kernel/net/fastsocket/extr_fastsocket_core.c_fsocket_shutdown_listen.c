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
struct socket {TYPE_1__* ops; TYPE_2__* sk; } ;
struct file {struct socket* private_data; struct file* sub_file; } ;
struct TYPE_4__ {scalar_t__ sk_state; } ;
struct TYPE_3__ {int (* shutdown ) (struct socket*,int) ;} ;

/* Variables and functions */
 scalar_t__ TCP_LISTEN ; 
 int stub1 (struct socket*,int) ; 
 int stub2 (struct socket*,int) ; 
 int stub3 (struct socket*,int) ; 

int fsocket_shutdown_listen(struct file *file, int how)
{
	struct socket *sock;
	int err;

	sock = file->private_data;
	if (sock->sk->sk_state == TCP_LISTEN) {
		struct file *sfile = file->sub_file;

		err = sock->ops->shutdown(sock, how);
		if (!err && sfile && sfile->private_data) {
			struct socket *ssock;

			ssock = sfile->private_data;
			err = ssock->ops->shutdown(ssock, how);
		}
	} else {
		err = sock->ops->shutdown(sock, how);
	}

	return err;
}