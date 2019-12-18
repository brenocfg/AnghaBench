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
typedef  void* u8 ;
struct dlm_master_list_entry {scalar_t__ type; int /*<<< orphan*/  maybe_map; void* master; void* new_master; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  wq; int /*<<< orphan*/  woken; } ;
struct dlm_lock_resource {int dummy; } ;
struct dlm_ctxt {void* node_num; int /*<<< orphan*/  name; int /*<<< orphan*/  master_lock; int /*<<< orphan*/  spinlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int DLM_MIGRATE_RESPONSE_MASTERY_REF ; 
 scalar_t__ DLM_MLE_MIGRATION ; 
 int EEXIST ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  __dlm_insert_mle (struct dlm_ctxt*,struct dlm_master_list_entry*) ; 
 int /*<<< orphan*/  __dlm_mle_detach_hb_events (struct dlm_ctxt*,struct dlm_master_list_entry*) ; 
 int /*<<< orphan*/  __dlm_unlink_mle (struct dlm_ctxt*,struct dlm_master_list_entry*) ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int dlm_find_mle (struct dlm_ctxt*,struct dlm_master_list_entry**,char*,unsigned int) ; 
 int /*<<< orphan*/  dlm_init_mle (struct dlm_master_list_entry*,scalar_t__,struct dlm_ctxt*,struct dlm_lock_resource*,char const*,unsigned int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned int,...) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  set_bit (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dlm_add_migration_mle(struct dlm_ctxt *dlm,
				 struct dlm_lock_resource *res,
				 struct dlm_master_list_entry *mle,
				 struct dlm_master_list_entry **oldmle,
				 const char *name, unsigned int namelen,
				 u8 new_master, u8 master)
{
	int found;
	int ret = 0;

	*oldmle = NULL;

	mlog_entry_void();

	assert_spin_locked(&dlm->spinlock);
	assert_spin_locked(&dlm->master_lock);

	/* caller is responsible for any ref taken here on oldmle */
	found = dlm_find_mle(dlm, oldmle, (char *)name, namelen);
	if (found) {
		struct dlm_master_list_entry *tmp = *oldmle;
		spin_lock(&tmp->spinlock);
		if (tmp->type == DLM_MLE_MIGRATION) {
			if (master == dlm->node_num) {
				/* ah another process raced me to it */
				mlog(0, "tried to migrate %.*s, but some "
				     "process beat me to it\n",
				     namelen, name);
				ret = -EEXIST;
			} else {
				/* bad.  2 NODES are trying to migrate! */
				mlog(ML_ERROR, "migration error  mle: "
				     "master=%u new_master=%u // request: "
				     "master=%u new_master=%u // "
				     "lockres=%.*s\n",
				     tmp->master, tmp->new_master,
				     master, new_master,
				     namelen, name);
				BUG();
			}
		} else {
			/* this is essentially what assert_master does */
			tmp->master = master;
			atomic_set(&tmp->woken, 1);
			wake_up(&tmp->wq);
			/* remove it so that only one mle will be found */
			__dlm_unlink_mle(dlm, tmp);
			__dlm_mle_detach_hb_events(dlm, tmp);
			ret = DLM_MIGRATE_RESPONSE_MASTERY_REF;
			mlog(0, "%s:%.*s: master=%u, newmaster=%u, "
			    "telling master to get ref for cleared out mle "
			    "during migration\n", dlm->name, namelen, name,
			    master, new_master);
		}
		spin_unlock(&tmp->spinlock);
	}

	/* now add a migration mle to the tail of the list */
	dlm_init_mle(mle, DLM_MLE_MIGRATION, dlm, res, name, namelen);
	mle->new_master = new_master;
	/* the new master will be sending an assert master for this.
	 * at that point we will get the refmap reference */
	mle->master = master;
	/* do this for consistency with other mle types */
	set_bit(new_master, mle->maybe_map);
	__dlm_insert_mle(dlm, mle);

	return ret;
}