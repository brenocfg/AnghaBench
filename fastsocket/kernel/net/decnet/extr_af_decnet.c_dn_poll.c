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
struct socket {struct sock* sk; } ;
struct sock {int dummy; } ;
struct file {int dummy; } ;
struct dn_scp {int /*<<< orphan*/  other_receive_queue; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 struct dn_scp* DN_SK (struct sock*) ; 
 int POLLRDBAND ; 
 int datagram_poll (struct file*,struct socket*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int dn_poll(struct file *file, struct socket *sock, poll_table  *wait)
{
	struct sock *sk = sock->sk;
	struct dn_scp *scp = DN_SK(sk);
	int mask = datagram_poll(file, sock, wait);

	if (!skb_queue_empty(&scp->other_receive_queue))
		mask |= POLLRDBAND;

	return mask;
}