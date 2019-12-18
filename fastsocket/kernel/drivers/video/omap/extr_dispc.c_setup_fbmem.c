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
struct omapfb_mem_region {long paddr; int alloc; int map; int type; unsigned long size; int /*<<< orphan*/ * vaddr; } ;
struct omapfb_mem_desc {int region_cnt; struct omapfb_mem_region* region; } ;
typedef  int /*<<< orphan*/  mem_start ;
typedef  int /*<<< orphan*/  mem_end ;
struct TYPE_4__ {int /*<<< orphan*/ ** res_map; struct omapfb_mem_desc mem_desc; TYPE_1__* fbdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DISPC_MEMTYPE_NUM ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int OMAPFB_MEMTYPE_SDRAM ; 
 int alloc_fbmem (struct omapfb_mem_region*) ; 
 int /*<<< orphan*/  cleanup_resmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__ dispc ; 
 int /*<<< orphan*/ * init_resmap (unsigned long,size_t) ; 
 int /*<<< orphan*/  memset (unsigned long*,int,int) ; 
 int mmap_kern (struct omapfb_mem_region*) ; 
 int /*<<< orphan*/  resmap_reserve_region (unsigned long,size_t) ; 

__attribute__((used)) static int setup_fbmem(struct omapfb_mem_desc *req_md)
{
	struct omapfb_mem_region	*rg;
	int i;
	int r;
	unsigned long			mem_start[DISPC_MEMTYPE_NUM];
	unsigned long			mem_end[DISPC_MEMTYPE_NUM];

	if (!req_md->region_cnt) {
		dev_err(dispc.fbdev->dev, "no memory regions defined\n");
		return -ENOENT;
	}

	rg = &req_md->region[0];
	memset(mem_start, 0xff, sizeof(mem_start));
	memset(mem_end, 0, sizeof(mem_end));

	for (i = 0; i < req_md->region_cnt; i++, rg++) {
		int mtype;
		if (rg->paddr) {
			rg->alloc = 0;
			if (rg->vaddr == NULL) {
				rg->map = 1;
				if ((r = mmap_kern(rg)) < 0)
					return r;
			}
		} else {
			if (rg->type != OMAPFB_MEMTYPE_SDRAM) {
				dev_err(dispc.fbdev->dev,
					"unsupported memory type\n");
				return -EINVAL;
			}
			rg->alloc = rg->map = 1;
			if ((r = alloc_fbmem(rg)) < 0)
				return r;
		}
		mtype = rg->type;

		if (rg->paddr < mem_start[mtype])
			mem_start[mtype] = rg->paddr;
		if (rg->paddr + rg->size > mem_end[mtype])
			mem_end[mtype] = rg->paddr + rg->size;
	}

	for (i = 0; i < DISPC_MEMTYPE_NUM; i++) {
		unsigned long start;
		size_t size;
		if (mem_end[i] == 0)
			continue;
		start = mem_start[i];
		size = mem_end[i] - start;
		dispc.res_map[i] = init_resmap(start, size);
		r = -ENOMEM;
		if (dispc.res_map[i] == NULL)
			goto fail;
		/* Initial state is that everything is reserved. This
		 * includes possible holes as well, which will never be
		 * freed.
		 */
		resmap_reserve_region(start, size);
	}

	dispc.mem_desc = *req_md;

	return 0;
fail:
	for (i = 0; i < DISPC_MEMTYPE_NUM; i++) {
		if (dispc.res_map[i] != NULL)
			cleanup_resmap(dispc.res_map[i]);
	}
	return r;
}