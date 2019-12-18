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
struct smb_sb_info {int dummy; } ;
struct smb_request {int rq_slen; int rq_bytes_sent; size_t rq_iovlen; int /*<<< orphan*/  rq_flags; struct kvec* rq_iov; struct smb_sb_info* rq_server; } ;
struct msghdr {int msg_flags; } ;
struct kvec {int dummy; } ;
struct TYPE_2__ {scalar_t__ sk_state; } ;

/* Variables and functions */
 int EIO ; 
 int MSG_DONTWAIT ; 
 int MSG_NOSIGNAL ; 
 int /*<<< orphan*/  SMB_REQ_TRANSMITTED ; 
 scalar_t__ TCP_ESTABLISHED ; 
 int kernel_sendmsg (struct socket*,struct msghdr*,struct kvec*,size_t,int) ; 
 struct socket* server_sock (struct smb_sb_info*) ; 
 int /*<<< orphan*/  smb_move_iov (struct kvec**,size_t*,struct kvec*,int) ; 

int
smb_send_request(struct smb_request *req)
{
	struct smb_sb_info *server = req->rq_server;
	struct socket *sock;
	struct msghdr msg = {.msg_flags = MSG_NOSIGNAL | MSG_DONTWAIT};
        int slen = req->rq_slen - req->rq_bytes_sent;
	int result = -EIO;
	struct kvec iov[4];
	struct kvec *p = req->rq_iov;
	size_t num = req->rq_iovlen;

	sock = server_sock(server);
	if (!sock)
		goto out;
	if (sock->sk->sk_state != TCP_ESTABLISHED)
		goto out;

	/* Dont repeat bytes */
	if (req->rq_bytes_sent)
		smb_move_iov(&p, &num, iov, req->rq_bytes_sent);

	result = kernel_sendmsg(sock, &msg, p, num, slen);

	if (result >= 0) {
		req->rq_bytes_sent += result;
		if (req->rq_bytes_sent >= req->rq_slen)
			req->rq_flags |= SMB_REQ_TRANSMITTED;
	}
out:
	return result;
}