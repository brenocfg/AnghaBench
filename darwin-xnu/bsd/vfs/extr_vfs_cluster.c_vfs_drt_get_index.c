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
typedef  scalar_t__ u_int64_t ;
typedef  scalar_t__ u_int32_t ;
struct vfs_drt_clustermap {scalar_t__ scm_modulus; scalar_t__ scm_lastclean; int /*<<< orphan*/  scm_iskips; int /*<<< orphan*/  scm_buckets; } ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 scalar_t__ DRT_ALIGN_ADDRESS (scalar_t__) ; 
 int /*<<< orphan*/  DRT_BITVECTOR_CLEAR (struct vfs_drt_clustermap*,scalar_t__) ; 
 int /*<<< orphan*/  DRT_DEBUG_INSERT ; 
 scalar_t__ DRT_HASH (struct vfs_drt_clustermap*,scalar_t__) ; 
 scalar_t__ DRT_HASH_GET_COUNT (struct vfs_drt_clustermap*,scalar_t__) ; 
 scalar_t__ DRT_HASH_NEXT (struct vfs_drt_clustermap*,scalar_t__) ; 
 int /*<<< orphan*/  DRT_HASH_SET_ADDRESS (struct vfs_drt_clustermap*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  DRT_HASH_SET_COUNT (struct vfs_drt_clustermap*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ DRT_HASH_VACANT (struct vfs_drt_clustermap*,scalar_t__) ; 
 scalar_t__ KERN_FAILURE ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ vfs_drt_alloc_map (struct vfs_drt_clustermap**) ; 
 scalar_t__ vfs_drt_search_index (struct vfs_drt_clustermap*,scalar_t__,int*) ; 
 int /*<<< orphan*/  vfs_drt_trace (struct vfs_drt_clustermap*,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static kern_return_t
vfs_drt_get_index(struct vfs_drt_clustermap **cmapp, u_int64_t offset, int *indexp, int recursed)
{
	struct vfs_drt_clustermap *cmap;
	kern_return_t	kret;
	u_int32_t	index;
	u_int32_t	i;

	cmap = *cmapp;

	/* look for an existing entry */
	kret = vfs_drt_search_index(cmap, offset, indexp);
	if (kret == KERN_SUCCESS)
		return(kret);

	/* need to allocate an entry */
	offset = DRT_ALIGN_ADDRESS(offset);
	index = DRT_HASH(cmap, offset);

	/* scan from the index forwards looking for a vacant slot */
	for (i = 0; i < cmap->scm_modulus; i++) {
		/* slot vacant? */
		if (DRT_HASH_VACANT(cmap, index) || DRT_HASH_GET_COUNT(cmap,index) == 0) {
			cmap->scm_buckets++;
			if (index < cmap->scm_lastclean)
				cmap->scm_lastclean = index;
			DRT_HASH_SET_ADDRESS(cmap, index, offset);
			DRT_HASH_SET_COUNT(cmap, index, 0);
			DRT_BITVECTOR_CLEAR(cmap, index);
			*indexp = index;
			vfs_drt_trace(cmap, DRT_DEBUG_INSERT, (int)offset, i, 0, 0);
			return(KERN_SUCCESS);
		}
		cmap->scm_iskips += i;
		index = DRT_HASH_NEXT(cmap, index);
	}

	/*
	 * We haven't found a vacant slot, so the map is full.  If we're not
	 * already recursed, try reallocating/compacting it.
	 */
	if (recursed)
		return(KERN_FAILURE);
	kret = vfs_drt_alloc_map(cmapp);
	if (kret == KERN_SUCCESS) {
		/* now try to insert again */
		kret = vfs_drt_get_index(cmapp, offset, indexp, 1);
	}
	return(kret);
}