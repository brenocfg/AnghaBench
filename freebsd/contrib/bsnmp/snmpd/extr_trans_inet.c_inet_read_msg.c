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
struct port_input {size_t length; int /*<<< orphan*/  fd; int /*<<< orphan*/  peerlen; int /*<<< orphan*/  peer; int /*<<< orphan*/  buflen; int /*<<< orphan*/  buf; } ;
struct msghdr {int msg_iovlen; char* msg_control; int msg_flags; int /*<<< orphan*/  msg_controllen; struct iovec* msg_iov; int /*<<< orphan*/  msg_namelen; int /*<<< orphan*/  msg_name; } ;
struct iovec {int /*<<< orphan*/  iov_len; int /*<<< orphan*/  iov_base; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  inTooLong; int /*<<< orphan*/  silentDrops; } ;

/* Variables and functions */
 int MSG_TRUNC ; 
 int /*<<< orphan*/  RECV_CBUF_SIZE ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int recvmsg (int /*<<< orphan*/ ,struct msghdr*,int /*<<< orphan*/ ) ; 
 TYPE_1__ snmpd_stats ; 

__attribute__((used)) static int
inet_read_msg(struct port_input *pi, struct msghdr *msg, char *cbuf)
{
	struct iovec iov[1];

	iov[0].iov_base = pi->buf;
	iov[0].iov_len = pi->buflen;

	msg->msg_name = pi->peer;
	msg->msg_namelen = pi->peerlen;
	msg->msg_iov = iov;
	msg->msg_iovlen = 1;
	msg->msg_control = cbuf;
	msg->msg_controllen = RECV_CBUF_SIZE;
	msg->msg_flags = 0;

	memset(cbuf, 0, RECV_CBUF_SIZE);

	const ssize_t len = recvmsg(pi->fd, msg, 0);

	if (len == -1 || len == 0)
		/* receive error */
		return (-1);

	if (msg->msg_flags & MSG_TRUNC) {
		/* truncated - drop */
		snmpd_stats.silentDrops++;
		snmpd_stats.inTooLong++;
		return (-1);
	}

	pi->length = (size_t)len;

	return (0);
}