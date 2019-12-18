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
struct dlm_direntry {int master_nodeid; int length; int /*<<< orphan*/  list; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int DLM_RESNAME_MAXLEN ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 size_t dir_hash (struct dlm_ls*,char*,int) ; 
 int /*<<< orphan*/  kfree (struct dlm_direntry*) ; 
 struct dlm_direntry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 struct dlm_direntry* search_bucket (struct dlm_ls*,char*,int,size_t) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_entry(struct dlm_ls *ls, int nodeid, char *name,
		     int namelen, int *r_nodeid)
{
	struct dlm_direntry *de, *tmp;
	uint32_t bucket;

	bucket = dir_hash(ls, name, namelen);

	spin_lock(&ls->ls_dirtbl[bucket].lock);
	de = search_bucket(ls, name, namelen, bucket);
	if (de) {
		*r_nodeid = de->master_nodeid;
		spin_unlock(&ls->ls_dirtbl[bucket].lock);
		if (*r_nodeid == nodeid)
			return -EEXIST;
		return 0;
	}

	spin_unlock(&ls->ls_dirtbl[bucket].lock);

	if (namelen > DLM_RESNAME_MAXLEN)
		return -EINVAL;

	de = kzalloc(sizeof(struct dlm_direntry) + namelen, GFP_NOFS);
	if (!de)
		return -ENOMEM;

	de->master_nodeid = nodeid;
	de->length = namelen;
	memcpy(de->name, name, namelen);

	spin_lock(&ls->ls_dirtbl[bucket].lock);
	tmp = search_bucket(ls, name, namelen, bucket);
	if (tmp) {
		kfree(de);
		de = tmp;
	} else {
		list_add_tail(&de->list, &ls->ls_dirtbl[bucket].list);
	}
	*r_nodeid = de->master_nodeid;
	spin_unlock(&ls->ls_dirtbl[bucket].lock);
	return 0;
}