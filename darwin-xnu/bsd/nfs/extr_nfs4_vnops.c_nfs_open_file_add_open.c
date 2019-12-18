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
typedef  int /*<<< orphan*/  uint32_t ;
struct nfs_open_file {int /*<<< orphan*/  nof_lock; int /*<<< orphan*/  nof_opencnt; int /*<<< orphan*/  nof_rw_drw; int /*<<< orphan*/  nof_w_drw; int /*<<< orphan*/  nof_r_drw; int /*<<< orphan*/  nof_rw_dw; int /*<<< orphan*/  nof_w_dw; int /*<<< orphan*/  nof_r_dw; int /*<<< orphan*/  nof_rw; int /*<<< orphan*/  nof_w; int /*<<< orphan*/  nof_r; int /*<<< orphan*/  nof_d_rw_drw; int /*<<< orphan*/  nof_d_w_drw; int /*<<< orphan*/  nof_d_r_drw; int /*<<< orphan*/  nof_d_rw_dw; int /*<<< orphan*/  nof_d_w_dw; int /*<<< orphan*/  nof_d_r_dw; int /*<<< orphan*/  nof_d_rw; int /*<<< orphan*/  nof_d_w; int /*<<< orphan*/  nof_d_r; int /*<<< orphan*/  nof_deny; int /*<<< orphan*/  nof_access; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_OPEN_SHARE_ACCESS_BOTH ; 
 int /*<<< orphan*/  NFS_OPEN_SHARE_ACCESS_READ ; 
 int /*<<< orphan*/  NFS_OPEN_SHARE_ACCESS_WRITE ; 
 int /*<<< orphan*/  NFS_OPEN_SHARE_DENY_NONE ; 
 int /*<<< orphan*/  NFS_OPEN_SHARE_DENY_WRITE ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 

void
nfs_open_file_add_open(struct nfs_open_file *nofp, uint32_t accessMode, uint32_t denyMode, int delegated)
{
	lck_mtx_lock(&nofp->nof_lock);
	nofp->nof_access |= accessMode;
	nofp->nof_deny |= denyMode;

	if (delegated) {
		if (denyMode == NFS_OPEN_SHARE_DENY_NONE) {
			if (accessMode == NFS_OPEN_SHARE_ACCESS_READ)
				nofp->nof_d_r++;
			else if (accessMode == NFS_OPEN_SHARE_ACCESS_WRITE)
				nofp->nof_d_w++;
			else if (accessMode == NFS_OPEN_SHARE_ACCESS_BOTH)
				nofp->nof_d_rw++;
		} else if (denyMode == NFS_OPEN_SHARE_DENY_WRITE) {
			if (accessMode == NFS_OPEN_SHARE_ACCESS_READ)
				nofp->nof_d_r_dw++;
			else if (accessMode == NFS_OPEN_SHARE_ACCESS_WRITE)
				nofp->nof_d_w_dw++;
			else if (accessMode == NFS_OPEN_SHARE_ACCESS_BOTH)
				nofp->nof_d_rw_dw++;
		} else { /* NFS_OPEN_SHARE_DENY_BOTH */
			if (accessMode == NFS_OPEN_SHARE_ACCESS_READ)
				nofp->nof_d_r_drw++;
			else if (accessMode == NFS_OPEN_SHARE_ACCESS_WRITE)
				nofp->nof_d_w_drw++;
			else if (accessMode == NFS_OPEN_SHARE_ACCESS_BOTH)
				nofp->nof_d_rw_drw++;
		}
	} else {
		if (denyMode == NFS_OPEN_SHARE_DENY_NONE) {
			if (accessMode == NFS_OPEN_SHARE_ACCESS_READ)
				nofp->nof_r++;
			else if (accessMode == NFS_OPEN_SHARE_ACCESS_WRITE)
				nofp->nof_w++;
			else if (accessMode == NFS_OPEN_SHARE_ACCESS_BOTH)
				nofp->nof_rw++;
		} else if (denyMode == NFS_OPEN_SHARE_DENY_WRITE) {
			if (accessMode == NFS_OPEN_SHARE_ACCESS_READ)
				nofp->nof_r_dw++;
			else if (accessMode == NFS_OPEN_SHARE_ACCESS_WRITE)
				nofp->nof_w_dw++;
			else if (accessMode == NFS_OPEN_SHARE_ACCESS_BOTH)
				nofp->nof_rw_dw++;
		} else { /* NFS_OPEN_SHARE_DENY_BOTH */
			if (accessMode == NFS_OPEN_SHARE_ACCESS_READ)
				nofp->nof_r_drw++;
			else if (accessMode == NFS_OPEN_SHARE_ACCESS_WRITE)
				nofp->nof_w_drw++;
			else if (accessMode == NFS_OPEN_SHARE_ACCESS_BOTH)
				nofp->nof_rw_drw++;
		}
	}

	nofp->nof_opencnt++;
	lck_mtx_unlock(&nofp->nof_lock);
}