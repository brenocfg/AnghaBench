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
struct gre_cisco_protocol {size_t priority; } ;

/* Variables and functions */
 int EINVAL ; 
 struct gre_cisco_protocol* cmpxchg (struct gre_cisco_protocol**,struct gre_cisco_protocol*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gre_cisco_proto_list ; 
 int /*<<< orphan*/  synchronize_net () ; 

int gre_cisco_unregister(struct gre_cisco_protocol *del_proto)
{
	struct gre_cisco_protocol **proto = (struct gre_cisco_protocol **)
					    &gre_cisco_proto_list[del_proto->priority];
	int ret;

	ret = (cmpxchg(proto, del_proto, NULL) == del_proto) ? 0 : -EINVAL;

	if (ret)
		return ret;

	synchronize_net();
	return 0;
}