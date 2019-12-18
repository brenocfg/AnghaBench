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
struct socket {TYPE_1__* sk; } ;
struct smb_sb_info {struct file* sock_file; int /*<<< orphan*/  data_ready; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sk_data_ready; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERBOSE (char*,struct socket*) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 struct socket* server_sock (struct smb_sb_info*) ; 

void
smb_close_socket(struct smb_sb_info *server)
{
	struct file * file = server->sock_file;

	if (file) {
		struct socket *sock = server_sock(server);

		VERBOSE("closing socket %p\n", sock);
		sock->sk->sk_data_ready = server->data_ready;
		server->sock_file = NULL;
		fput(file);
	}
}