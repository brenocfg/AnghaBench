#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sadb_msg {int sadb_msg_errno; scalar_t__ sadb_msg_seq; } ;
struct TYPE_3__ {int (* dump ) (struct pfkey_sock*) ;TYPE_2__* skb; } ;
struct pfkey_sock {TYPE_1__ dump; int /*<<< orphan*/  sk; } ;
struct TYPE_4__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BROADCAST_ONE ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  pfkey_broadcast (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfkey_can_dump (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfkey_terminate_dump (struct pfkey_sock*) ; 
 int /*<<< orphan*/  sock_net (int /*<<< orphan*/ *) ; 
 int stub1 (struct pfkey_sock*) ; 

__attribute__((used)) static int pfkey_do_dump(struct pfkey_sock *pfk)
{
	struct sadb_msg *hdr;
	int rc;

	rc = pfk->dump.dump(pfk);
	if (rc == -ENOBUFS)
		return 0;

	if (pfk->dump.skb) {
		if (!pfkey_can_dump(&pfk->sk))
			return 0;

		hdr = (struct sadb_msg *) pfk->dump.skb->data;
		hdr->sadb_msg_seq = 0;
		hdr->sadb_msg_errno = rc;
		pfkey_broadcast(pfk->dump.skb, GFP_ATOMIC, BROADCAST_ONE,
				&pfk->sk, sock_net(&pfk->sk));
		pfk->dump.skb = NULL;
	}

	pfkey_terminate_dump(pfk);
	return rc;
}