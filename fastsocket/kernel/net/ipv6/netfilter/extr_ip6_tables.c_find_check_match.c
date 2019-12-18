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
struct xt_mtchk_param {int dummy; } ;
struct xt_match {int /*<<< orphan*/  me; } ;
struct TYPE_4__ {struct xt_match* match; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; int /*<<< orphan*/  revision; } ;
struct TYPE_5__ {TYPE_1__ kernel; TYPE_3__ user; } ;
struct ip6t_entry_match {TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int ENOENT ; 
 scalar_t__ IS_ERR (struct xt_match*) ; 
 int PTR_ERR (struct xt_match*) ; 
 int check_match (struct ip6t_entry_match*,struct xt_mtchk_param*,unsigned int*) ; 
 int /*<<< orphan*/  duprintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 struct xt_match* try_then_request_module (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xt_find_match (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
find_check_match(struct ip6t_entry_match *m, struct xt_mtchk_param *par,
		 unsigned int *i)
{
	struct xt_match *match;
	int ret;

	match = try_then_request_module(xt_find_match(AF_INET6, m->u.user.name,
						      m->u.user.revision),
					"ip6t_%s", m->u.user.name);
	if (IS_ERR(match) || !match) {
		duprintf("find_check_match: `%s' not found\n", m->u.user.name);
		return match ? PTR_ERR(match) : -ENOENT;
	}
	m->u.kernel.match = match;

	ret = check_match(m, par, i);
	if (ret)
		goto err;

	return 0;
err:
	module_put(m->u.kernel.match->me);
	return ret;
}