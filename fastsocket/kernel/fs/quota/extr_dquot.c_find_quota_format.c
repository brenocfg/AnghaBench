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
struct quota_format_type {int qf_fmt_id; int /*<<< orphan*/  qf_owner; struct quota_format_type* qf_next; } ;
struct TYPE_2__ {int qm_fmt_id; int /*<<< orphan*/  qm_mod_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dq_list_lock ; 
 TYPE_1__* module_names ; 
 struct quota_format_type* quota_formats ; 
 scalar_t__ request_module (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct quota_format_type *find_quota_format(int id)
{
	struct quota_format_type *actqf;

	spin_lock(&dq_list_lock);
	for (actqf = quota_formats; actqf && actqf->qf_fmt_id != id;
	     actqf = actqf->qf_next)
		;
	if (!actqf || !try_module_get(actqf->qf_owner)) {
		int qm;

		spin_unlock(&dq_list_lock);
		
		for (qm = 0; module_names[qm].qm_fmt_id &&
			     module_names[qm].qm_fmt_id != id; qm++)
			;
		if (!module_names[qm].qm_fmt_id ||
		    request_module(module_names[qm].qm_mod_name))
			return NULL;

		spin_lock(&dq_list_lock);
		for (actqf = quota_formats; actqf && actqf->qf_fmt_id != id;
		     actqf = actqf->qf_next)
			;
		if (actqf && !try_module_get(actqf->qf_owner))
			actqf = NULL;
	}
	spin_unlock(&dq_list_lock);
	return actqf;
}