#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct pf_rule* ptr; } ;
struct pf_state {int /*<<< orphan*/ * rt_kif; int /*<<< orphan*/  nat_src_node; int /*<<< orphan*/  rt_addr; TYPE_3__ rule; } ;
struct TYPE_5__ {TYPE_1__* cur; } ;
struct pf_rule {scalar_t__ rt; TYPE_2__ rpool; } ;
struct pf_addr {int dummy; } ;
typedef  scalar_t__ sa_family_t ;
struct TYPE_4__ {int /*<<< orphan*/ * kif; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 scalar_t__ PF_FASTROUTE ; 
 int /*<<< orphan*/  pf_map_addr (scalar_t__,struct pf_rule*,struct pf_addr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pf_set_rt_ifp(struct pf_state *s, struct pf_addr *saddr, sa_family_t af)
{
	struct pf_rule *r = s->rule.ptr;

	s->rt_kif = NULL;

	if (!r->rt || r->rt == PF_FASTROUTE)
		return;
	if ((af == AF_INET) || (af == AF_INET6)) {
		pf_map_addr(af, r, saddr, &s->rt_addr, NULL,
		    &s->nat_src_node);
		s->rt_kif = r->rpool.cur->kif;
	}

	return;
}