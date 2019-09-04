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

/* Variables and functions */
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  lck_attr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_grp_attr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_grp_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * null_hashlck_attr ; 
 int /*<<< orphan*/ * null_hashlck_grp ; 
 int /*<<< orphan*/ * null_hashlck_grp_attr ; 
 int /*<<< orphan*/  null_hashmtx ; 
 int /*<<< orphan*/  null_node_hashtbl ; 

int
nullfs_uninit()
{
	/* This gets called when the fs is uninstalled, there wasn't an exact
	 * equivalent in vfsops */
	lck_mtx_destroy(&null_hashmtx, null_hashlck_grp);
	FREE(null_node_hashtbl, M_TEMP);
	if (null_hashlck_grp_attr) {
		lck_grp_attr_free(null_hashlck_grp_attr);
		null_hashlck_grp_attr = NULL;
	}
	if (null_hashlck_grp) {
		lck_grp_free(null_hashlck_grp);
		null_hashlck_grp = NULL;
	}
	if (null_hashlck_attr) {
		lck_attr_free(null_hashlck_attr);
		null_hashlck_attr = NULL;
	}
	return (0);
}