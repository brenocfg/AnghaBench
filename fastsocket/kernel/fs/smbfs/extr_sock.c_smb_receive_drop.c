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
struct smb_sb_info {int smb_read; scalar_t__ smb_len; int /*<<< orphan*/  rstate; int /*<<< orphan*/  header; } ;
struct msghdr {unsigned int msg_flags; int /*<<< orphan*/ * msg_control; scalar_t__ msg_namelen; int /*<<< orphan*/ * msg_name; } ;
struct kvec {int iov_len; int /*<<< orphan*/  iov_base; } ;
struct TYPE_2__ {scalar_t__ sk_state; } ;

/* Variables and functions */
 int EIO ; 
 unsigned int MSG_DONTWAIT ; 
 unsigned int MSG_NOSIGNAL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  SMB_RECV_END ; 
 scalar_t__ TCP_ESTABLISHED ; 
 int /*<<< orphan*/  VERBOSE (char*,int) ; 
 int /*<<< orphan*/  drop_buffer ; 
 int kernel_recvmsg (struct socket*,struct msghdr*,struct kvec*,int,int,unsigned int) ; 
 struct socket* server_sock (struct smb_sb_info*) ; 
 int smb_len (int /*<<< orphan*/ ) ; 

int
smb_receive_drop(struct smb_sb_info *server)
{
	struct socket *sock;
	unsigned int flags;
	struct kvec iov;
	struct msghdr msg;
	int rlen = smb_len(server->header) - server->smb_read + 4;
	int result = -EIO;

	if (rlen > PAGE_SIZE)
		rlen = PAGE_SIZE;

	sock = server_sock(server);
	if (!sock)
		goto out;
	if (sock->sk->sk_state != TCP_ESTABLISHED)
		goto out;

	flags = MSG_DONTWAIT | MSG_NOSIGNAL;
	iov.iov_base = drop_buffer;
	iov.iov_len = PAGE_SIZE;
	msg.msg_flags = flags;
	msg.msg_name = NULL;
	msg.msg_namelen = 0;
	msg.msg_control = NULL;

	result = kernel_recvmsg(sock, &msg, &iov, 1, rlen, flags);

	VERBOSE("read: %d\n", result);
	if (result < 0) {
		VERBOSE("receive error: %d\n", result);
		goto out;
	}
	server->smb_read += result;

	if (server->smb_read >= server->smb_len)
		server->rstate = SMB_RECV_END;

out:
	return result;
}