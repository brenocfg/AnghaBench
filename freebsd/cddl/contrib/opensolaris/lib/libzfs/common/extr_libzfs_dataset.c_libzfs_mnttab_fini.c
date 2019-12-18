#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* mnt_mntopts; TYPE_2__* mnt_fstype; TYPE_2__* mnt_mountp; TYPE_2__* mnt_special; } ;
struct TYPE_8__ {TYPE_1__ mtn_mt; } ;
typedef  TYPE_2__ mnttab_node_t ;
struct TYPE_9__ {int /*<<< orphan*/  libzfs_mnttab_cache_lock; int /*<<< orphan*/  libzfs_mnttab_cache; } ;
typedef  TYPE_3__ libzfs_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  avl_destroy (int /*<<< orphan*/ *) ; 
 TYPE_2__* avl_destroy_nodes (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 

void
libzfs_mnttab_fini(libzfs_handle_t *hdl)
{
	void *cookie = NULL;
	mnttab_node_t *mtn;

	while ((mtn = avl_destroy_nodes(&hdl->libzfs_mnttab_cache, &cookie))
	    != NULL) {
		free(mtn->mtn_mt.mnt_special);
		free(mtn->mtn_mt.mnt_mountp);
		free(mtn->mtn_mt.mnt_fstype);
		free(mtn->mtn_mt.mnt_mntopts);
		free(mtn);
	}
	avl_destroy(&hdl->libzfs_mnttab_cache);
	(void) pthread_mutex_destroy(&hdl->libzfs_mnttab_cache_lock);
}