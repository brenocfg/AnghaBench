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
 int EBUSY ; 
 int /*<<< orphan*/ * cmpxchg (struct gre_cisco_protocol**,int /*<<< orphan*/ *,struct gre_cisco_protocol*) ; 
 int /*<<< orphan*/ * gre_cisco_proto_list ; 

int gre_cisco_register(struct gre_cisco_protocol *newp)
{
	struct gre_cisco_protocol **proto = (struct gre_cisco_protocol **)
					    &gre_cisco_proto_list[newp->priority];

	return (cmpxchg(proto, NULL, newp) == NULL) ? 0 : -EBUSY;
}