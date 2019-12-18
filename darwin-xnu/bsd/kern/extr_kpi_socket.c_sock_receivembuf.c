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
struct msghdr {scalar_t__ msg_iovlen; int /*<<< orphan*/ * msg_iov; } ;
typedef  int /*<<< orphan*/  socket_t ;
typedef  int /*<<< orphan*/  mbuf_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  sock_receive_internal (int /*<<< orphan*/ ,struct msghdr*,int /*<<< orphan*/ *,int,size_t*) ; 

errno_t
sock_receivembuf(socket_t sock, struct msghdr *msg, mbuf_t *data, int flags,
    size_t *recvlen)
{
	if (data == NULL || recvlen == 0 || *recvlen <= 0 || (msg != NULL &&
	    (msg->msg_iov != NULL || msg->msg_iovlen != 0)))
		return (EINVAL);

	return (sock_receive_internal(sock, msg, data, flags, recvlen));
}