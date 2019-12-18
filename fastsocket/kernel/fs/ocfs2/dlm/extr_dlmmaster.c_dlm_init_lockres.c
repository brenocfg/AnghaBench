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
struct TYPE_2__ {unsigned int len; int /*<<< orphan*/  hash; scalar_t__ name; } ;
struct dlm_lock_resource {int /*<<< orphan*/  refmap; int /*<<< orphan*/  lvb; int /*<<< orphan*/  tracking; scalar_t__ last_used; int /*<<< orphan*/  state; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  refs; struct dlm_ctxt* dlm; scalar_t__ inflight_locks; scalar_t__ migration_pending; int /*<<< orphan*/  asts_reserved; int /*<<< orphan*/  purge; int /*<<< orphan*/  recovering; int /*<<< orphan*/  dirty; int /*<<< orphan*/  blocked; int /*<<< orphan*/  converting; int /*<<< orphan*/  granted; int /*<<< orphan*/  hash_node; int /*<<< orphan*/  wq; TYPE_1__ lockname; } ;
struct dlm_ctxt {int /*<<< orphan*/  spinlock; int /*<<< orphan*/  tracking_list; int /*<<< orphan*/  res_cur_count; int /*<<< orphan*/  res_tot_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_LOCK_RES_IN_PROGRESS ; 
 int /*<<< orphan*/  DLM_LOCK_RES_OWNER_UNKNOWN ; 
 int DLM_LVB_LEN ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_grab (struct dlm_ctxt*) ; 
 int /*<<< orphan*/  dlm_lockid_hash (char const*,unsigned int) ; 
 int /*<<< orphan*/  dlm_set_lockres_owner (struct dlm_ctxt*,struct dlm_lock_resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dlm_init_lockres(struct dlm_ctxt *dlm,
			     struct dlm_lock_resource *res,
			     const char *name, unsigned int namelen)
{
	char *qname;

	/* If we memset here, we lose our reference to the kmalloc'd
	 * res->lockname.name, so be sure to init every field
	 * correctly! */

	qname = (char *) res->lockname.name;
	memcpy(qname, name, namelen);

	res->lockname.len = namelen;
	res->lockname.hash = dlm_lockid_hash(name, namelen);

	init_waitqueue_head(&res->wq);
	spin_lock_init(&res->spinlock);
	INIT_HLIST_NODE(&res->hash_node);
	INIT_LIST_HEAD(&res->granted);
	INIT_LIST_HEAD(&res->converting);
	INIT_LIST_HEAD(&res->blocked);
	INIT_LIST_HEAD(&res->dirty);
	INIT_LIST_HEAD(&res->recovering);
	INIT_LIST_HEAD(&res->purge);
	INIT_LIST_HEAD(&res->tracking);
	atomic_set(&res->asts_reserved, 0);
	res->migration_pending = 0;
	res->inflight_locks = 0;

	/* put in dlm_lockres_release */
	dlm_grab(dlm);
	res->dlm = dlm;

	kref_init(&res->refs);

	atomic_inc(&dlm->res_tot_count);
	atomic_inc(&dlm->res_cur_count);

	/* just for consistency */
	spin_lock(&res->spinlock);
	dlm_set_lockres_owner(dlm, res, DLM_LOCK_RES_OWNER_UNKNOWN);
	spin_unlock(&res->spinlock);

	res->state = DLM_LOCK_RES_IN_PROGRESS;

	res->last_used = 0;

	spin_lock(&dlm->spinlock);
	list_add_tail(&res->tracking, &dlm->tracking_list);
	spin_unlock(&dlm->spinlock);

	memset(res->lvb, 0, DLM_LVB_LEN);
	memset(res->refmap, 0, sizeof(res->refmap));
}