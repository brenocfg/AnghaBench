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
struct smb_sb_info {scalar_t__ smb_read; int smb_len; scalar_t__ header; void* rstate; } ;
struct TYPE_2__ {scalar_t__ sk_state; } ;

/* Variables and functions */
 int EIO ; 
 int ENODATA ; 
 int /*<<< orphan*/  PARANOIA (char*,int) ; 
 scalar_t__ SMB_HEADER_LEN ; 
 scalar_t__ SMB_MAX_PACKET_SIZE ; 
 void* SMB_RECV_DROP ; 
 void* SMB_RECV_HCOMPLETE ; 
 scalar_t__ TCP_ESTABLISHED ; 
 int /*<<< orphan*/  VERBOSE (char*,int) ; 
 int _recvfrom (struct socket*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 struct socket* server_sock (struct smb_sb_info*) ; 
 int smb_get_length (struct socket*,unsigned char*) ; 

int
smb_receive_header(struct smb_sb_info *server)
{
	struct socket *sock;
	int result = 0;
	unsigned char peek_buf[4];

	result = -EIO; 
	sock = server_sock(server);
	if (!sock)
		goto out;
	if (sock->sk->sk_state != TCP_ESTABLISHED)
		goto out;

	if (!server->smb_read) {
		result = smb_get_length(sock, peek_buf);
		if (result < 0) {
			if (result == -ENODATA)
				result = 0;
			goto out;
		}
		server->smb_len = result + 4;

		if (server->smb_len < SMB_HEADER_LEN) {
			PARANOIA("short packet: %d\n", result);
			server->rstate = SMB_RECV_DROP;
			result = -EIO;
			goto out;
		}
		if (server->smb_len > SMB_MAX_PACKET_SIZE) {
			PARANOIA("long packet: %d\n", result);
			server->rstate = SMB_RECV_DROP;
			result = -EIO;
			goto out;
		}
	}

	result = _recvfrom(sock, server->header + server->smb_read,
			   SMB_HEADER_LEN - server->smb_read, 0);
	VERBOSE("_recvfrom: %d\n", result);
	if (result < 0) {
		VERBOSE("receive error: %d\n", result);
		goto out;
	}
	server->smb_read += result;

	if (server->smb_read == SMB_HEADER_LEN)
		server->rstate = SMB_RECV_HCOMPLETE;
out:
	return result;
}