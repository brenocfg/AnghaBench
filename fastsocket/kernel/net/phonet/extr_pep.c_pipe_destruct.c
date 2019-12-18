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
struct sock {int /*<<< orphan*/  sk_receive_queue; } ;
struct pep_sock {int /*<<< orphan*/  ctrlreq_queue; } ;

/* Variables and functions */
 struct pep_sock* pep_sk (struct sock*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pipe_destruct(struct sock *sk)
{
	struct pep_sock *pn = pep_sk(sk);

	skb_queue_purge(&sk->sk_receive_queue);
	skb_queue_purge(&pn->ctrlreq_queue);
}