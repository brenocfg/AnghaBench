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
struct xfrm_tmpl {int dummy; } ;
struct xfrm_algo_desc {scalar_t__ available; } ;
struct sadb_prop {int dummy; } ;
struct sadb_comb {int dummy; } ;

/* Variables and functions */
 scalar_t__ aalg_tmpl_set (struct xfrm_tmpl*,struct xfrm_algo_desc*) ; 
 struct xfrm_algo_desc* xfrm_aalg_get_byidx (int) ; 

__attribute__((used)) static int count_ah_combs(struct xfrm_tmpl *t)
{
	int i, sz = 0;

	for (i = 0; ; i++) {
		struct xfrm_algo_desc *aalg = xfrm_aalg_get_byidx(i);
		if (!aalg)
			break;
		if (aalg_tmpl_set(t, aalg) && aalg->available)
			sz += sizeof(struct sadb_comb);
	}
	return sz + sizeof(struct sadb_prop);
}