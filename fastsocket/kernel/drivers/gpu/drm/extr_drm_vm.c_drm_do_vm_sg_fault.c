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
struct vm_fault {struct page* page; scalar_t__ virtual_address; } ;
struct vm_area_struct {unsigned long vm_start; TYPE_1__* vm_file; struct drm_local_map* vm_private_data; } ;
struct page {int dummy; } ;
struct drm_sg_mem {struct page** pagelist; scalar_t__ virtual; } ;
struct drm_local_map {unsigned long offset; } ;
struct drm_file {TYPE_2__* minor; } ;
struct drm_device {struct drm_sg_mem* sg; } ;
struct TYPE_4__ {struct drm_device* dev; } ;
struct TYPE_3__ {struct drm_file* private_data; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 int VM_FAULT_SIGBUS ; 
 int /*<<< orphan*/  get_page (struct page*) ; 

__attribute__((used)) static int drm_do_vm_sg_fault(struct vm_area_struct *vma, struct vm_fault *vmf)
{
	struct drm_local_map *map = vma->vm_private_data;
	struct drm_file *priv = vma->vm_file->private_data;
	struct drm_device *dev = priv->minor->dev;
	struct drm_sg_mem *entry = dev->sg;
	unsigned long offset;
	unsigned long map_offset;
	unsigned long page_offset;
	struct page *page;

	if (!entry)
		return VM_FAULT_SIGBUS;	/* Error */
	if (!entry->pagelist)
		return VM_FAULT_SIGBUS;	/* Nothing allocated */

	offset = (unsigned long)vmf->virtual_address - vma->vm_start;
	map_offset = map->offset - (unsigned long)dev->sg->virtual;
	page_offset = (offset >> PAGE_SHIFT) + (map_offset >> PAGE_SHIFT);
	page = entry->pagelist[page_offset];
	get_page(page);
	vmf->page = page;

	return 0;
}