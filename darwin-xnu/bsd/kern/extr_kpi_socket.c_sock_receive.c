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
struct msghdr {int msg_iovlen; TYPE_1__* msg_iov; } ;
typedef  int /*<<< orphan*/  socket_t ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_2__ {scalar_t__ iov_len; int /*<<< orphan*/ * iov_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  sock_receive_internal (int /*<<< orphan*/ ,struct msghdr*,int /*<<< orphan*/ *,int,size_t*) ; 

errno_t
sock_receive(socket_t sock, struct msghdr *msg, int flags, size_t *recvdlen)
{
	if ((msg == NULL) || (msg->msg_iovlen < 1) ||
	    (msg->msg_iov[0].iov_len == 0) ||
	    (msg->msg_iov[0].iov_base == NULL))
		return (EINVAL);

	return (sock_receive_internal(sock, msg, NULL, flags, recvdlen));
}