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
struct sock {int dummy; } ;
struct pep_sock {int /*<<< orphan*/  pipe_handle; int /*<<< orphan*/  ctrlreq_queue; int /*<<< orphan*/  hlist; int /*<<< orphan*/  ackq; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PN_PIPE_INVALID_HANDLE ; 
 struct pep_sock* pep_sk (struct sock*) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pep_init(struct sock *sk)
{
	struct pep_sock *pn = pep_sk(sk);

	INIT_HLIST_HEAD(&pn->ackq);
	INIT_HLIST_HEAD(&pn->hlist);
	skb_queue_head_init(&pn->ctrlreq_queue);
	pn->pipe_handle = PN_PIPE_INVALID_HANDLE;
	return 0;
}