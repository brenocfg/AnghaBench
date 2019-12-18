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
struct xt_mtdtor_param {TYPE_2__* match; int /*<<< orphan*/  family; int /*<<< orphan*/  matchinfo; } ;
struct TYPE_3__ {TYPE_2__* match; } ;
struct ebt_entry_match {int /*<<< orphan*/  data; TYPE_1__ u; } ;
struct TYPE_4__ {int /*<<< orphan*/  me; int /*<<< orphan*/  (* destroy ) (struct xt_mtdtor_param*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NFPROTO_BRIDGE ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct xt_mtdtor_param*) ; 

__attribute__((used)) static inline int
ebt_cleanup_match(struct ebt_entry_match *m, unsigned int *i)
{
	struct xt_mtdtor_param par;

	if (i && (*i)-- == 0)
		return 1;

	par.match     = m->u.match;
	par.matchinfo = m->data;
	par.family    = NFPROTO_BRIDGE;
	if (par.match->destroy != NULL)
		par.match->destroy(&par);
	module_put(par.match->me);
	return 0;
}