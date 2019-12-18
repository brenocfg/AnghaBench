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
struct sock {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  len; } ;
struct l2cap_pinfo {TYPE_1__* conn; } ;
struct TYPE_2__ {int /*<<< orphan*/  hcon; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct sock*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int hci_send_acl (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct l2cap_pinfo* l2cap_pi (struct sock*) ; 

__attribute__((used)) static inline int l2cap_do_send(struct sock *sk, struct sk_buff *skb)
{
	struct l2cap_pinfo *pi = l2cap_pi(sk);
	int err;

	BT_DBG("sk %p, skb %p len %d", sk, skb, skb->len);

	err = hci_send_acl(pi->conn->hcon, skb, 0);
	if (err < 0)
		kfree_skb(skb);

	return err;
}