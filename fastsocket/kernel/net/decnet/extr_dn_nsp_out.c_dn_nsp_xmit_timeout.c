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
struct dn_scp {int /*<<< orphan*/  persist; int /*<<< orphan*/  other_xmit_queue; int /*<<< orphan*/  data_xmit_queue; } ;

/* Variables and functions */
 struct dn_scp* DN_SK (struct sock*) ; 
 int /*<<< orphan*/  dn_nsp_output (struct sock*) ; 
 int /*<<< orphan*/  dn_nsp_persist (struct sock*) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 

int dn_nsp_xmit_timeout(struct sock *sk)
{
	struct dn_scp *scp = DN_SK(sk);

	dn_nsp_output(sk);

	if (!skb_queue_empty(&scp->data_xmit_queue) ||
	    !skb_queue_empty(&scp->other_xmit_queue))
		scp->persist = dn_nsp_persist(sk);

	return 0;
}