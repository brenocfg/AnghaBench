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
#define  OVS_SAMPLE_ATTR_ACTIONS 129 
#define  OVS_SAMPLE_ATTR_PROBABILITY 128 
 int do_execute_actions (struct datapath*,struct sk_buff*,struct nlattr*,int,int) ; 
 int /*<<< orphan*/  net_random () ; 
 struct nlattr* nla_data (struct nlattr const*) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr const*) ; 
 int nla_len (struct nlattr const*) ; 
 struct nlattr* nla_next (struct nlattr const*,int*) ; 
 int nla_type (struct nlattr const*) ; 

__attribute__((used)) static int sample(struct datapath *dp, struct sk_buff *skb,
		  const struct nlattr *attr)
{
	const struct nlattr *acts_list = NULL;
	const struct nlattr *a;
	int rem;

	for (a = nla_data(attr), rem = nla_len(attr); rem > 0;
		 a = nla_next(a, &rem)) {
		switch (nla_type(a)) {
		case OVS_SAMPLE_ATTR_PROBABILITY:
			if (net_random() >= nla_get_u32(a))
				return 0;
			break;

		case OVS_SAMPLE_ATTR_ACTIONS:
			acts_list = a;
			break;
		}
	}

	return do_execute_actions(dp, skb, nla_data(acts_list),
						 nla_len(acts_list), true);
}