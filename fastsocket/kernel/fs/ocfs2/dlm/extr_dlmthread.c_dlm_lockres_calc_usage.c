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
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct dlm_lock_resource {int /*<<< orphan*/  spinlock; TYPE_1__ lockname; } ;
struct dlm_ctxt {int /*<<< orphan*/  spinlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __dlm_lockres_calc_usage (struct dlm_ctxt*,struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  mlog_entry (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void dlm_lockres_calc_usage(struct dlm_ctxt *dlm,
			    struct dlm_lock_resource *res)
{
	mlog_entry("%.*s\n", res->lockname.len, res->lockname.name);
	spin_lock(&dlm->spinlock);
	spin_lock(&res->spinlock);

	__dlm_lockres_calc_usage(dlm, res);

	spin_unlock(&res->spinlock);
	spin_unlock(&dlm->spinlock);
}