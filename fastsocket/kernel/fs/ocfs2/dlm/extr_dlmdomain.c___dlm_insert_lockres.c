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
struct qstr {int /*<<< orphan*/  hash; } ;
struct hlist_head {int dummy; } ;
struct dlm_lock_resource {int /*<<< orphan*/  hash_node; struct qstr lockname; } ;
struct dlm_ctxt {int /*<<< orphan*/  spinlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlm_lockres_get (struct dlm_lock_resource*) ; 
 struct hlist_head* dlm_lockres_hash (struct dlm_ctxt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,struct hlist_head*) ; 

void __dlm_insert_lockres(struct dlm_ctxt *dlm,
		       struct dlm_lock_resource *res)
{
	struct hlist_head *bucket;
	struct qstr *q;

	assert_spin_locked(&dlm->spinlock);

	q = &res->lockname;
	bucket = dlm_lockres_hash(dlm, q->hash);

	/* get a reference for our hashtable */
	dlm_lockres_get(res);

	hlist_add_head(&res->hash_node, bucket);
}