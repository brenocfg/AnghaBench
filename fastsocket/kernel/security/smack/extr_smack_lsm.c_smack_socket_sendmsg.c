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
struct socket {int /*<<< orphan*/  sk; } ;
struct sockaddr_in {scalar_t__ sin_family; } ;
struct msghdr {scalar_t__ msg_name; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int smack_netlabel_send (int /*<<< orphan*/ ,struct sockaddr_in*) ; 

__attribute__((used)) static int smack_socket_sendmsg(struct socket *sock, struct msghdr *msg,
				int size)
{
	struct sockaddr_in *sip = (struct sockaddr_in *) msg->msg_name;

	/*
	 * Perfectly reasonable for this to be NULL
	 */
	if (sip == NULL || sip->sin_family != AF_INET)
		return 0;

	return smack_netlabel_send(sock->sk, sip);
}