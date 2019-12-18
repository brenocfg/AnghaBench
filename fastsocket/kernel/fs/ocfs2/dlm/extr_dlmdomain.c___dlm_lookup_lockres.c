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
struct dlm_lock_resource {int state; int /*<<< orphan*/  spinlock; } ;
struct dlm_ctxt {int /*<<< orphan*/  spinlock; } ;

/* Variables and functions */
 int DLM_LOCK_RES_DROPPING_REF ; 
 struct dlm_lock_resource* __dlm_lookup_lockres_full (struct dlm_ctxt*,char const*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlm_lockres_put (struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  mlog_entry (char*,unsigned int,char const*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct dlm_lock_resource * __dlm_lookup_lockres(struct dlm_ctxt *dlm,
						const char *name,
						unsigned int len,
						unsigned int hash)
{
	struct dlm_lock_resource *res = NULL;

	mlog_entry("%.*s\n", len, name);

	assert_spin_locked(&dlm->spinlock);

	res = __dlm_lookup_lockres_full(dlm, name, len, hash);
	if (res) {
		spin_lock(&res->spinlock);
		if (res->state & DLM_LOCK_RES_DROPPING_REF) {
			spin_unlock(&res->spinlock);
			dlm_lockres_put(res);
			return NULL;
		}
		spin_unlock(&res->spinlock);
	}

	return res;
}