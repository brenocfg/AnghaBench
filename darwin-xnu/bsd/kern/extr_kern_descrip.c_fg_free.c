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
struct fileglob {int /*<<< orphan*/  fg_lock; int /*<<< orphan*/  fg_cred; int /*<<< orphan*/ * fg_vn_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_ZONE (struct fileglob*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_VALID_CRED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_FILEGLOB ; 
 int /*<<< orphan*/  OSAddAtomic (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fg_vn_data_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  file_lck_grp ; 
 int /*<<< orphan*/  kauth_cred_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_file_label_destroy (struct fileglob*) ; 
 int /*<<< orphan*/  nfiles ; 

void
fg_free(struct fileglob *fg)
{
	OSAddAtomic(-1, &nfiles);

	if (fg->fg_vn_data) {
		fg_vn_data_free(fg->fg_vn_data);
		fg->fg_vn_data = NULL;
	}

	if (IS_VALID_CRED(fg->fg_cred)) {
		kauth_cred_unref(&fg->fg_cred);
	}
	lck_mtx_destroy(&fg->fg_lock, file_lck_grp);

#if CONFIG_MACF
	mac_file_label_destroy(fg);
#endif
	FREE_ZONE(fg, sizeof *fg, M_FILEGLOB);
}