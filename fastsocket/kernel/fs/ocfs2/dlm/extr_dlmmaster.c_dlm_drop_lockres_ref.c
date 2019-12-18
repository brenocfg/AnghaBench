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
struct TYPE_2__ {char* name; unsigned int len; } ;
struct dlm_lock_resource {int /*<<< orphan*/  owner; TYPE_1__ lockname; } ;
struct dlm_deref_lockres {unsigned int namelen; int /*<<< orphan*/  name; int /*<<< orphan*/  node_idx; } ;
struct dlm_ctxt {int /*<<< orphan*/  name; int /*<<< orphan*/  key; int /*<<< orphan*/  node_num; } ;
typedef  int /*<<< orphan*/  deref ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DLM_DEREF_LOCKRES_MSG ; 
 int /*<<< orphan*/  ML_ERROR ; 
 unsigned int O2NM_MAX_NAME_LEN ; 
 int /*<<< orphan*/  dlm_print_one_lock_resource (struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,unsigned int) ; 
 int /*<<< orphan*/  memset (struct dlm_deref_lockres*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int,char const*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int o2net_send_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dlm_deref_lockres*,int,int /*<<< orphan*/ ,int*) ; 

int dlm_drop_lockres_ref(struct dlm_ctxt *dlm, struct dlm_lock_resource *res)
{
	struct dlm_deref_lockres deref;
	int ret = 0, r;
	const char *lockname;
	unsigned int namelen;

	lockname = res->lockname.name;
	namelen = res->lockname.len;
	BUG_ON(namelen > O2NM_MAX_NAME_LEN);

	mlog(0, "%s:%.*s: sending deref to %d\n",
	     dlm->name, namelen, lockname, res->owner);
	memset(&deref, 0, sizeof(deref));
	deref.node_idx = dlm->node_num;
	deref.namelen = namelen;
	memcpy(deref.name, lockname, namelen);

	ret = o2net_send_message(DLM_DEREF_LOCKRES_MSG, dlm->key,
				 &deref, sizeof(deref), res->owner, &r);
	if (ret < 0)
		mlog_errno(ret);
	else if (r < 0) {
		/* BAD.  other node says I did not have a ref. */
		mlog(ML_ERROR,"while dropping ref on %s:%.*s "
		    "(master=%u) got %d.\n", dlm->name, namelen,
		    lockname, res->owner, r);
		dlm_print_one_lock_resource(res);
		BUG();
	}
	return ret;
}