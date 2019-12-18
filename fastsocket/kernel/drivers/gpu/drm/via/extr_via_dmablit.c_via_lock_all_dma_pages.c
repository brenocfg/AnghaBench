#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct TYPE_8__ {unsigned long num_pages; scalar_t__ direction; void* state; int /*<<< orphan*/ * pages; } ;
typedef  TYPE_1__ drm_via_sg_info_t ;
struct TYPE_9__ {int mem_addr; int num_lines; int mem_stride; } ;
typedef  TYPE_2__ drm_via_dmablit_t ;
struct TYPE_11__ {int /*<<< orphan*/  mmap_sem; } ;
struct TYPE_10__ {TYPE_6__* mm; } ;

/* Variables and functions */
 scalar_t__ DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 unsigned long VIA_PFN (int) ; 
 TYPE_5__* current ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 void* dr_via_pages_locked ; 
 int get_user_pages (TYPE_5__*,TYPE_6__*,unsigned long,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vzalloc (int) ; 

__attribute__((used)) static int
via_lock_all_dma_pages(drm_via_sg_info_t *vsg,  drm_via_dmablit_t *xfer)
{
	int ret;
	unsigned long first_pfn = VIA_PFN(xfer->mem_addr);
	vsg->num_pages = VIA_PFN(xfer->mem_addr + (xfer->num_lines * xfer->mem_stride - 1)) -
		first_pfn + 1;

	vsg->pages = vzalloc(sizeof(struct page *) * vsg->num_pages);
	if (NULL == vsg->pages)
		return -ENOMEM;
	down_read(&current->mm->mmap_sem);
	ret = get_user_pages(current, current->mm,
			     (unsigned long)xfer->mem_addr,
			     vsg->num_pages,
			     (vsg->direction == DMA_FROM_DEVICE),
			     0, vsg->pages, NULL);

	up_read(&current->mm->mmap_sem);
	if (ret != vsg->num_pages) {
		if (ret < 0)
			return ret;
		vsg->state = dr_via_pages_locked;
		return -EINVAL;
	}
	vsg->state = dr_via_pages_locked;
	DRM_DEBUG("DMA pages locked\n");
	return 0;
}