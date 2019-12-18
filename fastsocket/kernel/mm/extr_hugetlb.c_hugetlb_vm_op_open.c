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
struct vm_area_struct {int dummy; } ;
struct resv_map {int /*<<< orphan*/  refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 struct resv_map* vma_resv_map (struct vm_area_struct*) ; 

__attribute__((used)) static void hugetlb_vm_op_open(struct vm_area_struct *vma)
{
	struct resv_map *reservations = vma_resv_map(vma);

	/*
	 * This new VMA should share its siblings reservation map if present.
	 * The VMA will only ever have a valid reservation map pointer where
	 * it is being copied for another still existing VMA.  As that VMA
	 * has a reference to the reservation map it cannot dissappear until
	 * after this open call completes.  It is therefore safe to take a
	 * new reference here without additional locking.
	 */
	if (reservations)
		kref_get(&reservations->refs);
}