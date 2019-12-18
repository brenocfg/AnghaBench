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
struct xfrm_selector {int dport; int dport_mask; int sport; int sport_mask; scalar_t__ proto; scalar_t__ ifindex; int /*<<< orphan*/  prefixlen_s; int /*<<< orphan*/  saddr; int /*<<< orphan*/  prefixlen_d; int /*<<< orphan*/  daddr; } ;
struct flowi {scalar_t__ proto; scalar_t__ oif; int /*<<< orphan*/  fl4_src; int /*<<< orphan*/  fl4_dst; } ;

/* Variables and functions */
 scalar_t__ addr_match (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int xfrm_flowi_dport (struct flowi*) ; 
 int xfrm_flowi_sport (struct flowi*) ; 

__attribute__((used)) static inline int
__xfrm4_selector_match(struct xfrm_selector *sel, struct flowi *fl)
{
	return  addr_match(&fl->fl4_dst, &sel->daddr, sel->prefixlen_d) &&
		addr_match(&fl->fl4_src, &sel->saddr, sel->prefixlen_s) &&
		!((xfrm_flowi_dport(fl) ^ sel->dport) & sel->dport_mask) &&
		!((xfrm_flowi_sport(fl) ^ sel->sport) & sel->sport_mask) &&
		(fl->proto == sel->proto || !sel->proto) &&
		(fl->oif == sel->ifindex || !sel->ifindex);
}