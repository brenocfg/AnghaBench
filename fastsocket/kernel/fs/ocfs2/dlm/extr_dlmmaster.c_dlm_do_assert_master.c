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
typedef  int /*<<< orphan*/  u32 ;
struct dlm_node_iter {int dummy; } ;
struct dlm_master_list_entry {int dummy; } ;
struct TYPE_2__ {char* name; unsigned int len; } ;
struct dlm_lock_resource {int /*<<< orphan*/  wq; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  state; TYPE_1__ lockname; } ;
struct dlm_ctxt {int /*<<< orphan*/  spinlock; int /*<<< orphan*/  master_lock; int /*<<< orphan*/  key; int /*<<< orphan*/  node_num; } ;
struct dlm_assert_master {unsigned int namelen; int /*<<< orphan*/  flags; int /*<<< orphan*/  name; int /*<<< orphan*/  node_idx; } ;
typedef  int /*<<< orphan*/  assert ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DLM_ASSERT_MASTER_MSG ; 
 int DLM_ASSERT_RESPONSE_MASTERY_REF ; 
 int DLM_ASSERT_RESPONSE_REASSERT ; 
 int /*<<< orphan*/  DLM_LOCK_RES_SETREF_INPROG ; 
 int /*<<< orphan*/  ML_ERROR ; 
 unsigned int O2NM_MAX_NAME_LEN ; 
 int /*<<< orphan*/  __dlm_put_mle (struct dlm_master_list_entry*) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 scalar_t__ dlm_find_mle (struct dlm_ctxt*,struct dlm_master_list_entry**,char*,unsigned int) ; 
 int /*<<< orphan*/  dlm_is_host_down (int) ; 
 int /*<<< orphan*/  dlm_lockres_set_refmap_bit (int,struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  dlm_node_iter_init (void*,struct dlm_node_iter*) ; 
 int dlm_node_iter_next (struct dlm_node_iter*) ; 
 int /*<<< orphan*/  dlm_print_one_mle (struct dlm_master_list_entry*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,unsigned int) ; 
 int /*<<< orphan*/  memset (struct dlm_assert_master*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned int,...) ; 
 int o2net_send_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dlm_assert_master*,int,int,int*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dlm_do_assert_master(struct dlm_ctxt *dlm,
				struct dlm_lock_resource *res,
				void *nodemap, u32 flags)
{
	struct dlm_assert_master assert;
	int to, tmpret;
	struct dlm_node_iter iter;
	int ret = 0;
	int reassert;
	const char *lockname = res->lockname.name;
	unsigned int namelen = res->lockname.len;

	BUG_ON(namelen > O2NM_MAX_NAME_LEN);

	spin_lock(&res->spinlock);
	res->state |= DLM_LOCK_RES_SETREF_INPROG;
	spin_unlock(&res->spinlock);

again:
	reassert = 0;

	/* note that if this nodemap is empty, it returns 0 */
	dlm_node_iter_init(nodemap, &iter);
	while ((to = dlm_node_iter_next(&iter)) >= 0) {
		int r = 0;
		struct dlm_master_list_entry *mle = NULL;

		mlog(0, "sending assert master to %d (%.*s)\n", to,
		     namelen, lockname);
		memset(&assert, 0, sizeof(assert));
		assert.node_idx = dlm->node_num;
		assert.namelen = namelen;
		memcpy(assert.name, lockname, namelen);
		assert.flags = cpu_to_be32(flags);

		tmpret = o2net_send_message(DLM_ASSERT_MASTER_MSG, dlm->key,
					    &assert, sizeof(assert), to, &r);
		if (tmpret < 0) {
			mlog(0, "assert_master returned %d!\n", tmpret);
			if (!dlm_is_host_down(tmpret)) {
				mlog(ML_ERROR, "unhandled error=%d!\n", tmpret);
				BUG();
			}
			/* a node died.  finish out the rest of the nodes. */
			mlog(0, "link to %d went down!\n", to);
			/* any nonzero status return will do */
			ret = tmpret;
			r = 0;
		} else if (r < 0) {
			/* ok, something horribly messed.  kill thyself. */
			mlog(ML_ERROR,"during assert master of %.*s to %u, "
			     "got %d.\n", namelen, lockname, to, r);
			spin_lock(&dlm->spinlock);
			spin_lock(&dlm->master_lock);
			if (dlm_find_mle(dlm, &mle, (char *)lockname,
					 namelen)) {
				dlm_print_one_mle(mle);
				__dlm_put_mle(mle);
			}
			spin_unlock(&dlm->master_lock);
			spin_unlock(&dlm->spinlock);
			BUG();
		}

		if (r & DLM_ASSERT_RESPONSE_REASSERT &&
		    !(r & DLM_ASSERT_RESPONSE_MASTERY_REF)) {
				mlog(ML_ERROR, "%.*s: very strange, "
				     "master MLE but no lockres on %u\n",
				     namelen, lockname, to);
		}

		if (r & DLM_ASSERT_RESPONSE_REASSERT) {
			mlog(0, "%.*s: node %u create mles on other "
			     "nodes and requests a re-assert\n", 
			     namelen, lockname, to);
			reassert = 1;
		}
		if (r & DLM_ASSERT_RESPONSE_MASTERY_REF) {
			mlog(0, "%.*s: node %u has a reference to this "
			     "lockres, set the bit in the refmap\n",
			     namelen, lockname, to);
			spin_lock(&res->spinlock);
			dlm_lockres_set_refmap_bit(to, res);
			spin_unlock(&res->spinlock);
		}
	}

	if (reassert)
		goto again;

	spin_lock(&res->spinlock);
	res->state &= ~DLM_LOCK_RES_SETREF_INPROG;
	spin_unlock(&res->spinlock);
	wake_up(&res->wq);

	return ret;
}