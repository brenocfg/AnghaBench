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
struct vfs_drt_clustermap {scalar_t__ scm_modulus; } ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 scalar_t__ DRT_ALIGN_ADDRESS (scalar_t__) ; 
 int DRT_HASH (struct vfs_drt_clustermap*,scalar_t__) ; 
 scalar_t__ DRT_HASH_GET_ADDRESS (struct vfs_drt_clustermap*,int) ; 
 int DRT_HASH_NEXT (struct vfs_drt_clustermap*,int) ; 
 scalar_t__ DRT_HASH_VACANT (struct vfs_drt_clustermap*,int) ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 

__attribute__((used)) static kern_return_t
vfs_drt_search_index(struct vfs_drt_clustermap *cmap, u_int64_t offset, int *indexp)
{
	int		index;
	u_int32_t	i;

	offset = DRT_ALIGN_ADDRESS(offset);
	index = DRT_HASH(cmap, offset);

	/* traverse the hashtable */
	for (i = 0; i < cmap->scm_modulus; i++) {

		/*
		 * If the slot is vacant, we can stop.
		 */
		if (DRT_HASH_VACANT(cmap, index))
			break;

		/*
		 * If the address matches our offset, we have success.
		 */
		if (DRT_HASH_GET_ADDRESS(cmap, index) == offset) {
			*indexp = index;
			return(KERN_SUCCESS);
		}

		/*
		 * Move to the next slot, try again.
		 */
		index = DRT_HASH_NEXT(cmap, index);
	}
	/*
	 * It's not there.
	 */
	return(KERN_FAILURE);
}