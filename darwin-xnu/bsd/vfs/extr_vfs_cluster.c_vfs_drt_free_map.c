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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct vfs_drt_clustermap {scalar_t__ scm_modulus; } ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 scalar_t__ DRT_HASH_SMALL_MODULUS ; 
 int /*<<< orphan*/  DRT_LARGE_ALLOCATION ; 
 int /*<<< orphan*/  DRT_SMALL_ALLOCATION ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  kernel_map ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static kern_return_t
vfs_drt_free_map(struct vfs_drt_clustermap *cmap)
{
	kmem_free(kernel_map, (vm_offset_t)cmap, 
		  (cmap->scm_modulus == DRT_HASH_SMALL_MODULUS) ? DRT_SMALL_ALLOCATION : DRT_LARGE_ALLOCATION);
	return(KERN_SUCCESS);
}