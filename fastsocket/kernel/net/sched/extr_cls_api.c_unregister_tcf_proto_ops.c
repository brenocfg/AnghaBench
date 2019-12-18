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
struct tcf_proto_ops {struct tcf_proto_ops* next; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  cls_mod_lock ; 
 struct tcf_proto_ops* tcf_proto_base ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

int unregister_tcf_proto_ops(struct tcf_proto_ops *ops)
{
	struct tcf_proto_ops *t, **tp;
	int rc = -ENOENT;

	write_lock(&cls_mod_lock);
	for (tp = &tcf_proto_base; (t=*tp) != NULL; tp = &t->next)
		if (t == ops)
			break;

	if (!t)
		goto out;
	*tp = t->next;
	rc = 0;
out:
	write_unlock(&cls_mod_lock);
	return rc;
}