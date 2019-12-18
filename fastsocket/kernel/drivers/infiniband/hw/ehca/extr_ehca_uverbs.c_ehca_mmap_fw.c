#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct vm_area_struct {scalar_t__ vm_end; scalar_t__ vm_start; int /*<<< orphan*/ * vm_ops; int /*<<< orphan*/ * vm_private_data; int /*<<< orphan*/  vm_page_prot; } ;
struct TYPE_2__ {scalar_t__ fw_handle; } ;
struct h_galpas {TYPE_1__ user; } ;

/* Variables and functions */
 scalar_t__ EHCA_PAGESHIFT ; 
 scalar_t__ EHCA_PAGESIZE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ehca_gen_dbg (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ehca_gen_err (char*,int) ; 
 int /*<<< orphan*/  pgprot_noncached (int /*<<< orphan*/ ) ; 
 int remap_4k_pfn (struct vm_area_struct*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vm_ops ; 

__attribute__((used)) static int ehca_mmap_fw(struct vm_area_struct *vma, struct h_galpas *galpas,
			u32 *mm_count)
{
	int ret;
	u64 vsize, physical;

	vsize = vma->vm_end - vma->vm_start;
	if (vsize < EHCA_PAGESIZE) {
		ehca_gen_err("invalid vsize=%lx", vma->vm_end - vma->vm_start);
		return -EINVAL;
	}

	physical = galpas->user.fw_handle;
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	ehca_gen_dbg("vsize=%llx physical=%llx", vsize, physical);
	/* VM_IO | VM_RESERVED are set by remap_pfn_range() */
	ret = remap_4k_pfn(vma, vma->vm_start, physical >> EHCA_PAGESHIFT,
			   vma->vm_page_prot);
	if (unlikely(ret)) {
		ehca_gen_err("remap_pfn_range() failed ret=%i", ret);
		return -ENOMEM;
	}

	vma->vm_private_data = mm_count;
	(*mm_count)++;
	vma->vm_ops = &vm_ops;

	return 0;
}