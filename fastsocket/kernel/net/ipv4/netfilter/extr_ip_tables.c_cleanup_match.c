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
struct xt_mtdtor_param {TYPE_1__* match; int /*<<< orphan*/  family; int /*<<< orphan*/  matchinfo; } ;
struct TYPE_5__ {TYPE_1__* match; } ;
struct TYPE_6__ {TYPE_2__ kernel; } ;
struct ipt_entry_match {int /*<<< orphan*/  data; TYPE_3__ u; } ;
struct TYPE_4__ {int /*<<< orphan*/  me; int /*<<< orphan*/  (* destroy ) (struct xt_mtdtor_param*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NFPROTO_IPV4 ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct xt_mtdtor_param*) ; 

__attribute__((used)) static int
cleanup_match(struct ipt_entry_match *m, unsigned int *i)
{
	struct xt_mtdtor_param par;

	if (i && (*i)-- == 0)
		return 1;

	par.match     = m->u.kernel.match;
	par.matchinfo = m->data;
	par.family    = NFPROTO_IPV4;
	if (par.match->destroy != NULL)
		par.match->destroy(&par);
	module_put(par.match->me);
	return 0;
}