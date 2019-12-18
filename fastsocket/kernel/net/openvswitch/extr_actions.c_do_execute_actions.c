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
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct datapath {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
#define  OVS_ACTION_ATTR_OUTPUT 133 
#define  OVS_ACTION_ATTR_POP_VLAN 132 
#define  OVS_ACTION_ATTR_PUSH_VLAN 131 
#define  OVS_ACTION_ATTR_SAMPLE 130 
#define  OVS_ACTION_ATTR_SET 129 
#define  OVS_ACTION_ATTR_USERSPACE 128 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  do_output (struct datapath*,struct sk_buff*,int) ; 
 int execute_set_action (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  nla_data (struct nlattr const*) ; 
 int nla_get_u32 (struct nlattr const*) ; 
 struct nlattr* nla_next (struct nlattr const*,int*) ; 
 int nla_type (struct nlattr const*) ; 
 int /*<<< orphan*/  output_userspace (struct datapath*,struct sk_buff*,struct nlattr const*) ; 
 int pop_vlan (struct sk_buff*) ; 
 int push_vlan (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int sample (struct datapath*,struct sk_buff*,struct nlattr const*) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int do_execute_actions(struct datapath *dp, struct sk_buff *skb,
			const struct nlattr *attr, int len, bool keep_skb)
{
	/* Every output action needs a separate clone of 'skb', but the common
	 * case is just a single output action, so that doing a clone and
	 * then freeing the original skbuff is wasteful.  So the following code
	 * is slightly obscure just to avoid that. */
	int prev_port = -1;
	const struct nlattr *a;
	int rem;

	for (a = attr, rem = len; rem > 0;
	     a = nla_next(a, &rem)) {
		int err = 0;

		if (prev_port != -1) {
			do_output(dp, skb_clone(skb, GFP_ATOMIC), prev_port);
			prev_port = -1;
		}

		switch (nla_type(a)) {
		case OVS_ACTION_ATTR_OUTPUT:
			prev_port = nla_get_u32(a);
			break;

		case OVS_ACTION_ATTR_USERSPACE:
			output_userspace(dp, skb, a);
			break;

		case OVS_ACTION_ATTR_PUSH_VLAN:
			err = push_vlan(skb, nla_data(a));
			if (unlikely(err)) /* skb already freed. */
				return err;
			break;

		case OVS_ACTION_ATTR_POP_VLAN:
			err = pop_vlan(skb);
			break;

		case OVS_ACTION_ATTR_SET:
			err = execute_set_action(skb, nla_data(a));
			break;

		case OVS_ACTION_ATTR_SAMPLE:
			err = sample(dp, skb, a);
			break;
		}

		if (unlikely(err)) {
			kfree_skb(skb);
			return err;
		}
	}

	if (prev_port != -1) {
		if (keep_skb)
			skb = skb_clone(skb, GFP_ATOMIC);

		do_output(dp, skb, prev_port);
	} else if (!keep_skb)
		consume_skb(skb);

	return 0;
}