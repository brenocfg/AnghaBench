#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {int vm_flags; TYPE_2__* vm_file; } ;
struct resv_map {int /*<<< orphan*/  regions; } ;
struct inode {TYPE_1__* i_mapping; } ;
struct hstate {int dummy; } ;
struct address_space {struct inode* host; } ;
typedef  scalar_t__ pgoff_t ;
struct TYPE_4__ {struct address_space* f_mapping; } ;
struct TYPE_3__ {int /*<<< orphan*/  private_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPAGE_RESV_OWNER ; 
 int VM_MAYSHARE ; 
 scalar_t__ is_vma_resv_set (struct vm_area_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  region_add (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ vma_hugecache_offset (struct hstate*,struct vm_area_struct*,unsigned long) ; 
 struct resv_map* vma_resv_map (struct vm_area_struct*) ; 

__attribute__((used)) static void vma_commit_reservation(struct hstate *h,
			struct vm_area_struct *vma, unsigned long addr)
{
	struct address_space *mapping = vma->vm_file->f_mapping;
	struct inode *inode = mapping->host;

	if (vma->vm_flags & VM_MAYSHARE) {
		pgoff_t idx = vma_hugecache_offset(h, vma, addr);
		region_add(&inode->i_mapping->private_list, idx, idx + 1);

	} else if (is_vma_resv_set(vma, HPAGE_RESV_OWNER)) {
		pgoff_t idx = vma_hugecache_offset(h, vma, addr);
		struct resv_map *reservations = vma_resv_map(vma);

		/* Mark this page used in the map. */
		region_add(&reservations->regions, idx, idx + 1);
	}
}