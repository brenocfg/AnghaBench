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
struct xt_target {int /*<<< orphan*/  me; } ;
struct TYPE_5__ {struct xt_target* target; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/  revision; } ;
struct TYPE_6__ {TYPE_2__ kernel; TYPE_1__ user; } ;
struct arpt_entry_target {TYPE_3__ u; } ;
struct arpt_entry {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ IS_ERR (struct xt_target*) ; 
 int /*<<< orphan*/  NFPROTO_ARP ; 
 int PTR_ERR (struct xt_target*) ; 
 struct arpt_entry_target* arpt_get_target (struct arpt_entry*) ; 
 int check_entry (struct arpt_entry*,char const*) ; 
 int check_target (struct arpt_entry*,char const*) ; 
 int /*<<< orphan*/  duprintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 struct xt_target* try_then_request_module (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xt_find_target (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
find_check_entry(struct arpt_entry *e, const char *name, unsigned int size,
		 unsigned int *i)
{
	struct arpt_entry_target *t;
	struct xt_target *target;
	int ret;

	ret = check_entry(e, name);
	if (ret)
		return ret;

	t = arpt_get_target(e);
	target = try_then_request_module(xt_find_target(NFPROTO_ARP,
							t->u.user.name,
							t->u.user.revision),
					 "arpt_%s", t->u.user.name);
	if (IS_ERR(target) || !target) {
		duprintf("find_check_entry: `%s' not found\n", t->u.user.name);
		ret = target ? PTR_ERR(target) : -ENOENT;
		goto out;
	}
	t->u.kernel.target = target;

	ret = check_target(e, name);
	if (ret)
		goto err;

	(*i)++;
	return 0;
err:
	module_put(t->u.kernel.target->me);
out:
	return ret;
}