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
typedef  unsigned long u32 ;
struct rxrpc_sock {int dummy; } ;
struct msghdr {scalar_t__ msg_controllen; int msg_flags; } ;
struct cmsghdr {int cmsg_len; scalar_t__ cmsg_level; int cmsg_type; } ;
typedef  enum rxrpc_command { ____Placeholder_rxrpc_command } rxrpc_command ;

/* Variables and functions */
 int CMSG_ALIGN (int) ; 
 scalar_t__ CMSG_DATA (struct cmsghdr*) ; 
 struct cmsghdr* CMSG_FIRSTHDR (struct msghdr*) ; 
 struct cmsghdr* CMSG_NXTHDR (struct msghdr*,struct cmsghdr*) ; 
 int /*<<< orphan*/  CMSG_OK (struct msghdr*,struct cmsghdr*) ; 
 int EINVAL ; 
 int EISCONN ; 
 int MSG_CMSG_COMPAT ; 
#define  RXRPC_ABORT 130 
#define  RXRPC_ACCEPT 129 
 int RXRPC_CMD_ACCEPT ; 
 int RXRPC_CMD_SEND_ABORT ; 
 int RXRPC_CMD_SEND_DATA ; 
#define  RXRPC_USER_CALL_ID 128 
 scalar_t__ SOL_RXRPC ; 
 int /*<<< orphan*/  _debug (char*,unsigned long,...) ; 
 int /*<<< orphan*/  _leave (char*) ; 

__attribute__((used)) static int rxrpc_sendmsg_cmsg(struct rxrpc_sock *rx, struct msghdr *msg,
			      unsigned long *user_call_ID,
			      enum rxrpc_command *command,
			      u32 *abort_code,
			      bool server)
{
	struct cmsghdr *cmsg;
	int len;

	*command = RXRPC_CMD_SEND_DATA;

	if (msg->msg_controllen == 0)
		return -EINVAL;

	for (cmsg = CMSG_FIRSTHDR(msg); cmsg; cmsg = CMSG_NXTHDR(msg, cmsg)) {
		if (!CMSG_OK(msg, cmsg))
			return -EINVAL;

		len = cmsg->cmsg_len - CMSG_ALIGN(sizeof(struct cmsghdr));
		_debug("CMSG %d, %d, %d",
		       cmsg->cmsg_level, cmsg->cmsg_type, len);

		if (cmsg->cmsg_level != SOL_RXRPC)
			continue;

		switch (cmsg->cmsg_type) {
		case RXRPC_USER_CALL_ID:
			if (msg->msg_flags & MSG_CMSG_COMPAT) {
				if (len != sizeof(u32))
					return -EINVAL;
				*user_call_ID = *(u32 *) CMSG_DATA(cmsg);
			} else {
				if (len != sizeof(unsigned long))
					return -EINVAL;
				*user_call_ID = *(unsigned long *)
					CMSG_DATA(cmsg);
			}
			_debug("User Call ID %lx", *user_call_ID);
			break;

		case RXRPC_ABORT:
			if (*command != RXRPC_CMD_SEND_DATA)
				return -EINVAL;
			*command = RXRPC_CMD_SEND_ABORT;
			if (len != sizeof(*abort_code))
				return -EINVAL;
			*abort_code = *(unsigned int *) CMSG_DATA(cmsg);
			_debug("Abort %x", *abort_code);
			if (*abort_code == 0)
				return -EINVAL;
			break;

		case RXRPC_ACCEPT:
			if (*command != RXRPC_CMD_SEND_DATA)
				return -EINVAL;
			*command = RXRPC_CMD_ACCEPT;
			if (len != 0)
				return -EINVAL;
			if (!server)
				return -EISCONN;
			break;

		default:
			return -EINVAL;
		}
	}

	_leave(" = 0");
	return 0;
}