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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct afs_vlocation {TYPE_1__ vldb; int /*<<< orphan*/  lock; int /*<<< orphan*/  waitq; int /*<<< orphan*/  update; int /*<<< orphan*/  grave; int /*<<< orphan*/  link; int /*<<< orphan*/  usage; int /*<<< orphan*/  state; struct afs_cell* cell; } ;
struct afs_cell {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_VL_NEW ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _leave (char*,struct afs_vlocation*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct afs_vlocation* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct afs_vlocation *afs_vlocation_alloc(struct afs_cell *cell,
						 const char *name,
						 size_t namesz)
{
	struct afs_vlocation *vl;

	vl = kzalloc(sizeof(struct afs_vlocation), GFP_KERNEL);
	if (vl) {
		vl->cell = cell;
		vl->state = AFS_VL_NEW;
		atomic_set(&vl->usage, 1);
		INIT_LIST_HEAD(&vl->link);
		INIT_LIST_HEAD(&vl->grave);
		INIT_LIST_HEAD(&vl->update);
		init_waitqueue_head(&vl->waitq);
		spin_lock_init(&vl->lock);
		memcpy(vl->vldb.name, name, namesz);
	}

	_leave(" = %p", vl);
	return vl;
}