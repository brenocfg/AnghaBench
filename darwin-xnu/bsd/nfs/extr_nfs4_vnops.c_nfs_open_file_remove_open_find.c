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
typedef  int uint32_t ;
struct nfs_open_file {int nof_access; int nof_deny; int nof_r; int nof_d_r; int nof_rw; int nof_d_rw; int nof_r_dw; int nof_d_r_dw; int nof_rw_dw; int nof_d_rw_dw; int nof_r_drw; int nof_d_r_drw; int nof_w; int nof_d_w; int nof_w_dw; int nof_d_w_dw; int nof_w_drw; int nof_d_w_drw; int nof_rw_drw; int nof_d_rw_drw; } ;

/* Variables and functions */
 int NFS_OPEN_SHARE_ACCESS_BOTH ; 
 int NFS_OPEN_SHARE_ACCESS_READ ; 
 int NFS_OPEN_SHARE_ACCESS_WRITE ; 
 int NFS_OPEN_SHARE_DENY_NONE ; 
 int NFS_OPEN_SHARE_DENY_READ ; 
 int NFS_OPEN_SHARE_DENY_WRITE ; 

void
nfs_open_file_remove_open_find(
	struct nfs_open_file *nofp,
	uint32_t accessMode,
	uint32_t denyMode,
	uint32_t *newAccessMode,
	uint32_t *newDenyMode,
	int *delegated)
{
	/*
	 * Calculate new modes: a mode bit gets removed when there's only
	 * one count in all the corresponding counts
	 */
	*newAccessMode = nofp->nof_access;
	*newDenyMode = nofp->nof_deny;

	if ((accessMode & NFS_OPEN_SHARE_ACCESS_READ) &&
	    (nofp->nof_access & NFS_OPEN_SHARE_ACCESS_READ) &&
	    ((nofp->nof_r + nofp->nof_d_r +
	      nofp->nof_rw + nofp->nof_d_rw +
	      nofp->nof_r_dw + nofp->nof_d_r_dw +
	      nofp->nof_rw_dw + nofp->nof_d_rw_dw +
	      nofp->nof_r_drw + nofp->nof_d_r_drw +
	      nofp->nof_rw_dw + nofp->nof_d_rw_dw) == 1))
		*newAccessMode &= ~NFS_OPEN_SHARE_ACCESS_READ;
	if ((accessMode & NFS_OPEN_SHARE_ACCESS_WRITE) &&
	    (nofp->nof_access & NFS_OPEN_SHARE_ACCESS_WRITE) &&
	    ((nofp->nof_w + nofp->nof_d_w +
	      nofp->nof_rw + nofp->nof_d_rw +
	      nofp->nof_w_dw + nofp->nof_d_w_dw +
	      nofp->nof_rw_dw + nofp->nof_d_rw_dw +
	      nofp->nof_w_drw + nofp->nof_d_w_drw +
	      nofp->nof_rw_dw + nofp->nof_d_rw_dw) == 1))
		*newAccessMode &= ~NFS_OPEN_SHARE_ACCESS_WRITE;
	if ((denyMode & NFS_OPEN_SHARE_DENY_READ) &&
	    (nofp->nof_deny & NFS_OPEN_SHARE_DENY_READ) &&
	    ((nofp->nof_r_drw + nofp->nof_d_r_drw +
	      nofp->nof_w_drw + nofp->nof_d_w_drw +
	      nofp->nof_rw_drw + nofp->nof_d_rw_drw) == 1))
		*newDenyMode &= ~NFS_OPEN_SHARE_DENY_READ;
	if ((denyMode & NFS_OPEN_SHARE_DENY_WRITE) &&
	    (nofp->nof_deny & NFS_OPEN_SHARE_DENY_WRITE) &&
	    ((nofp->nof_r_drw + nofp->nof_d_r_drw +
	      nofp->nof_w_drw + nofp->nof_d_w_drw +
	      nofp->nof_rw_drw + nofp->nof_d_rw_drw +
	      nofp->nof_r_dw + nofp->nof_d_r_dw +
	      nofp->nof_w_dw + nofp->nof_d_w_dw +
	      nofp->nof_rw_dw + nofp->nof_d_rw_dw) == 1))
		*newDenyMode &= ~NFS_OPEN_SHARE_DENY_WRITE;

	/* Find the corresponding open access/deny mode counter. */
	if (denyMode == NFS_OPEN_SHARE_DENY_NONE) {
		if (accessMode == NFS_OPEN_SHARE_ACCESS_READ)
			*delegated = (nofp->nof_d_r != 0);
		else if (accessMode == NFS_OPEN_SHARE_ACCESS_WRITE)
			*delegated = (nofp->nof_d_w != 0);
		else if (accessMode == NFS_OPEN_SHARE_ACCESS_BOTH)
			*delegated = (nofp->nof_d_rw != 0);
		else
			*delegated = 0;
	} else if (denyMode == NFS_OPEN_SHARE_DENY_WRITE) {
		if (accessMode == NFS_OPEN_SHARE_ACCESS_READ)
			*delegated = (nofp->nof_d_r_dw != 0);
		else if (accessMode == NFS_OPEN_SHARE_ACCESS_WRITE)
			*delegated = (nofp->nof_d_w_dw != 0);
		else if (accessMode == NFS_OPEN_SHARE_ACCESS_BOTH)
			*delegated = (nofp->nof_d_rw_dw != 0);
		else
			*delegated = 0;
	} else { /* NFS_OPEN_SHARE_DENY_BOTH */
		if (accessMode == NFS_OPEN_SHARE_ACCESS_READ)
			*delegated = (nofp->nof_d_r_drw != 0);
		else if (accessMode == NFS_OPEN_SHARE_ACCESS_WRITE)
			*delegated = (nofp->nof_d_w_drw != 0);
		else if (accessMode == NFS_OPEN_SHARE_ACCESS_BOTH)
			*delegated = (nofp->nof_d_rw_drw != 0);
		else
			*delegated = 0;
	}
}