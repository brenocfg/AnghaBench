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
typedef  int uint32_t ;
struct dlm_rsb {int res_hash; int res_bucket; int res_nodeid; int /*<<< orphan*/  res_hashchain; int /*<<< orphan*/  res_ref; } ;
struct dlm_ls {int ls_rsbtbl_size; TYPE_1__* ls_rsbtbl; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int DLM_RESNAME_MAXLEN ; 
 int EBADR ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENOTBLK ; 
 unsigned int R_CREATE ; 
 int _search_rsb (struct dlm_ls*,char*,int,int,int /*<<< orphan*/ ,struct dlm_rsb**) ; 
 struct dlm_rsb* create_rsb (struct dlm_ls*,char*,int) ; 
 int dlm_dir_nodeid (struct dlm_rsb*) ; 
 int /*<<< orphan*/  dlm_free_rsb (struct dlm_rsb*) ; 
 scalar_t__ dlm_no_directory (struct dlm_ls*) ; 
 int dlm_our_nodeid () ; 
 int jhash (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int search_rsb (struct dlm_ls*,char*,int,int,unsigned int,struct dlm_rsb**) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int find_rsb(struct dlm_ls *ls, char *name, int namelen,
		    unsigned int flags, struct dlm_rsb **r_ret)
{
	struct dlm_rsb *r = NULL, *tmp;
	uint32_t hash, bucket;
	int error = -EINVAL;

	if (namelen > DLM_RESNAME_MAXLEN)
		goto out;

	if (dlm_no_directory(ls))
		flags |= R_CREATE;

	error = 0;
	hash = jhash(name, namelen, 0);
	bucket = hash & (ls->ls_rsbtbl_size - 1);

	error = search_rsb(ls, name, namelen, bucket, flags, &r);
	if (!error)
		goto out;

	if (error == -EBADR && !(flags & R_CREATE))
		goto out;

	/* the rsb was found but wasn't a master copy */
	if (error == -ENOTBLK)
		goto out;

	error = -ENOMEM;
	r = create_rsb(ls, name, namelen);
	if (!r)
		goto out;

	r->res_hash = hash;
	r->res_bucket = bucket;
	r->res_nodeid = -1;
	kref_init(&r->res_ref);

	/* With no directory, the master can be set immediately */
	if (dlm_no_directory(ls)) {
		int nodeid = dlm_dir_nodeid(r);
		if (nodeid == dlm_our_nodeid())
			nodeid = 0;
		r->res_nodeid = nodeid;
	}

	spin_lock(&ls->ls_rsbtbl[bucket].lock);
	error = _search_rsb(ls, name, namelen, bucket, 0, &tmp);
	if (!error) {
		spin_unlock(&ls->ls_rsbtbl[bucket].lock);
		dlm_free_rsb(r);
		r = tmp;
		goto out;
	}
	list_add(&r->res_hashchain, &ls->ls_rsbtbl[bucket].list);
	spin_unlock(&ls->ls_rsbtbl[bucket].lock);
	error = 0;
 out:
	*r_ret = r;
	return error;
}