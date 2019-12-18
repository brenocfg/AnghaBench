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
typedef  size_t uint32_t ;
struct dlm_ls {TYPE_1__* ls_dirtbl; } ;
struct dlm_direntry {int master_nodeid; int /*<<< orphan*/  list; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 size_t dir_hash (struct dlm_ls*,char*,int) ; 
 int /*<<< orphan*/  kfree (struct dlm_direntry*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_error (struct dlm_ls*,char*,int,...) ; 
 struct dlm_direntry* search_bucket (struct dlm_ls*,char*,int,size_t) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void dlm_dir_remove_entry(struct dlm_ls *ls, int nodeid, char *name, int namelen)
{
	struct dlm_direntry *de;
	uint32_t bucket;

	bucket = dir_hash(ls, name, namelen);

	spin_lock(&ls->ls_dirtbl[bucket].lock);

	de = search_bucket(ls, name, namelen, bucket);

	if (!de) {
		log_error(ls, "remove fr %u none", nodeid);
		goto out;
	}

	if (de->master_nodeid != nodeid) {
		log_error(ls, "remove fr %u ID %u", nodeid, de->master_nodeid);
		goto out;
	}

	list_del(&de->list);
	kfree(de);
 out:
	spin_unlock(&ls->ls_dirtbl[bucket].lock);
}