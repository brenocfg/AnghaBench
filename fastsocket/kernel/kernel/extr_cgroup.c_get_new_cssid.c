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
struct css_id {int id; int depth; } ;
struct cgroup_subsys {int /*<<< orphan*/  id_lock; int /*<<< orphan*/  idr; int /*<<< orphan*/  use_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CSS_ID_MAX ; 
 int ENOMEM ; 
 int ENOSPC ; 
 struct css_id* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int idr_get_new_above (int /*<<< orphan*/ *,struct css_id*,int,int*) ; 
 int /*<<< orphan*/  idr_pre_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct css_id*) ; 
 struct css_id* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct css_id *get_new_cssid(struct cgroup_subsys *ss, int depth)
{
	struct css_id *newid;
	int myid, error, size;

	BUG_ON(!ss->use_id);

	size = sizeof(*newid) + sizeof(unsigned short) * (depth + 1);
	newid = kzalloc(size, GFP_KERNEL);
	if (!newid)
		return ERR_PTR(-ENOMEM);
	/* get id */
	if (unlikely(!idr_pre_get(&ss->idr, GFP_KERNEL))) {
		error = -ENOMEM;
		goto err_out;
	}
	spin_lock(&ss->id_lock);
	/* Don't use 0. allocates an ID of 1-65535 */
	error = idr_get_new_above(&ss->idr, newid, 1, &myid);
	spin_unlock(&ss->id_lock);

	/* Returns error when there are no free spaces for new ID.*/
	if (error) {
		error = -ENOSPC;
		goto err_out;
	}
	if (myid > CSS_ID_MAX)
		goto remove_idr;

	newid->id = myid;
	newid->depth = depth;
	return newid;
remove_idr:
	error = -ENOSPC;
	spin_lock(&ss->id_lock);
	idr_remove(&ss->idr, myid);
	spin_unlock(&ss->id_lock);
err_out:
	kfree(newid);
	return ERR_PTR(error);

}