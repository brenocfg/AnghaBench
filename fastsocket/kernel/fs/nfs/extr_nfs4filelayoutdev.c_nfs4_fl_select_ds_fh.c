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
typedef  size_t u32 ;
struct pnfs_layout_segment {int dummy; } ;
struct nfs_fh {int dummy; } ;
struct nfs4_filelayout_segment {scalar_t__ stripe_type; int num_fh; struct nfs_fh** fh_array; } ;

/* Variables and functions */
 struct nfs4_filelayout_segment* FILELAYOUT_LSEG (struct pnfs_layout_segment*) ; 
 scalar_t__ STRIPE_SPARSE ; 
 size_t nfs4_fl_calc_ds_index (struct pnfs_layout_segment*,size_t) ; 

struct nfs_fh *
nfs4_fl_select_ds_fh(struct pnfs_layout_segment *lseg, u32 j)
{
	struct nfs4_filelayout_segment *flseg = FILELAYOUT_LSEG(lseg);
	u32 i;

	if (flseg->stripe_type == STRIPE_SPARSE) {
		if (flseg->num_fh == 1)
			i = 0;
		else if (flseg->num_fh == 0)
			/* Use the MDS OPEN fh set in nfs_read_rpcsetup */
			return NULL;
		else
			i = nfs4_fl_calc_ds_index(lseg, j);
	} else
		i = j;
	return flseg->fh_array[i];
}