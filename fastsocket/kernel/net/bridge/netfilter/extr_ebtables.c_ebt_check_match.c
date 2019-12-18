#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xt_mtchk_param {int /*<<< orphan*/  matchinfo; struct xt_match* match; struct ebt_entry* entryinfo; } ;
struct xt_match {int /*<<< orphan*/  me; } ;
struct TYPE_2__ {struct xt_match* match; int /*<<< orphan*/  name; } ;
struct ebt_entry_match {size_t match_size; int /*<<< orphan*/  data; TYPE_1__ u; } ;
struct ebt_entry {int watchers_offset; int invflags; int /*<<< orphan*/  ethproto; } ;

/* Variables and functions */
 int EBT_IPROTO ; 
 int EINVAL ; 
 int ENOENT ; 
 scalar_t__ IS_ERR (struct xt_match*) ; 
 int /*<<< orphan*/  NFPROTO_BRIDGE ; 
 int PTR_ERR (struct xt_match*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 struct xt_match* try_then_request_module (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int xt_check_match (struct xt_mtchk_param*,size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xt_find_match (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
ebt_check_match(struct ebt_entry_match *m, struct xt_mtchk_param *par,
		unsigned int *cnt)
{
	const struct ebt_entry *e = par->entryinfo;
	struct xt_match *match;
	size_t left = ((char *)e + e->watchers_offset) - (char *)m;
	int ret;

	if (left < sizeof(struct ebt_entry_match) ||
	    left - sizeof(struct ebt_entry_match) < m->match_size)
		return -EINVAL;

	match = try_then_request_module(xt_find_match(NFPROTO_BRIDGE,
		m->u.name, 0), "ebt_%s", m->u.name);
	if (IS_ERR(match))
		return PTR_ERR(match);
	if (match == NULL)
		return -ENOENT;
	m->u.match = match;

	par->match     = match;
	par->matchinfo = m->data;
	ret = xt_check_match(par, m->match_size,
	      e->ethproto, e->invflags & EBT_IPROTO);
	if (ret < 0) {
		module_put(match->me);
		return ret;
	}

	(*cnt)++;
	return 0;
}