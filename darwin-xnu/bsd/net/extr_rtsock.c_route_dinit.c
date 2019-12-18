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
struct protosw {int dummy; } ;
struct domain {int dom_flags; } ;

/* Variables and functions */
 int DOM_INITIALIZED ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  net_add_proto (struct protosw*,struct domain*,int) ; 
 int /*<<< orphan*/  route_init () ; 
 int route_proto_count ; 
 struct domain* routedomain ; 
 struct protosw* routesw ; 

__attribute__((used)) static void
route_dinit(struct domain *dp)
{
	struct protosw *pr;
	int i;

	VERIFY(!(dp->dom_flags & DOM_INITIALIZED));
	VERIFY(routedomain == NULL);

	routedomain = dp;

	for (i = 0, pr = &routesw[0]; i < route_proto_count; i++, pr++)
		net_add_proto(pr, dp, 1);

	route_init();
}