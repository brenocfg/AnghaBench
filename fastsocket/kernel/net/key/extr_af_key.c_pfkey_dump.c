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
typedef  scalar_t__ u8 ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct sadb_msg {int /*<<< orphan*/  sadb_msg_pid; int /*<<< orphan*/  sadb_msg_version; int /*<<< orphan*/  sadb_msg_satype; } ;
struct TYPE_3__ {int /*<<< orphan*/  state; } ;
struct TYPE_4__ {TYPE_1__ u; int /*<<< orphan*/  done; int /*<<< orphan*/ * dump; int /*<<< orphan*/  msg_pid; int /*<<< orphan*/  msg_version; } ;
struct pfkey_sock {TYPE_2__ dump; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int pfkey_do_dump (struct pfkey_sock*) ; 
 int /*<<< orphan*/ * pfkey_dump_sa ; 
 int /*<<< orphan*/  pfkey_dump_sa_done ; 
 scalar_t__ pfkey_satype2proto (int /*<<< orphan*/ ) ; 
 struct pfkey_sock* pfkey_sk (struct sock*) ; 
 int /*<<< orphan*/  xfrm_state_walk_init (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int pfkey_dump(struct sock *sk, struct sk_buff *skb, struct sadb_msg *hdr, void **ext_hdrs)
{
	u8 proto;
	struct pfkey_sock *pfk = pfkey_sk(sk);

	if (pfk->dump.dump != NULL)
		return -EBUSY;

	proto = pfkey_satype2proto(hdr->sadb_msg_satype);
	if (proto == 0)
		return -EINVAL;

	pfk->dump.msg_version = hdr->sadb_msg_version;
	pfk->dump.msg_pid = hdr->sadb_msg_pid;
	pfk->dump.dump = pfkey_dump_sa;
	pfk->dump.done = pfkey_dump_sa_done;
	xfrm_state_walk_init(&pfk->dump.u.state, proto);

	return pfkey_do_dump(pfk);
}