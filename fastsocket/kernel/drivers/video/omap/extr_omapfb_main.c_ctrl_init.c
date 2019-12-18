#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int region_cnt; TYPE_2__* region; } ;
struct omapfb_platform_data {TYPE_3__ mem_desc; } ;
struct omapfb_device {TYPE_3__ mem_desc; TYPE_4__* dev; TYPE_1__* ctrl; struct lcd_panel* panel; } ;
struct lcd_panel {int bpp; } ;
struct TYPE_9__ {struct omapfb_platform_data* platform_data; } ;
struct TYPE_7__ {void* size; int /*<<< orphan*/  vaddr; int /*<<< orphan*/  paddr; } ;
struct TYPE_6__ {int (* init ) (struct omapfb_device*,int /*<<< orphan*/ ,TYPE_3__*) ;} ;

/* Variables and functions */
 void* PAGE_ALIGN (int) ; 
 int* def_vram ; 
 int def_vram_cnt ; 
 int def_vxres ; 
 int def_vyres ; 
 int /*<<< orphan*/  dev_dbg (TYPE_4__*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,int) ; 
 int stub1 (struct omapfb_device*,int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static int ctrl_init(struct omapfb_device *fbdev)
{
	int r;
	int i;

	/* kernel/module vram parameters override boot tags/board config */
	if (def_vram_cnt) {
		for (i = 0; i < def_vram_cnt; i++)
			fbdev->mem_desc.region[i].size =
				PAGE_ALIGN(def_vram[i]);
		fbdev->mem_desc.region_cnt = i;
	} else {
		struct omapfb_platform_data *conf;

		conf = fbdev->dev->platform_data;
		fbdev->mem_desc = conf->mem_desc;
	}

	if (!fbdev->mem_desc.region_cnt) {
		struct lcd_panel *panel = fbdev->panel;
		int def_size;
		int bpp = panel->bpp;

		/* 12 bpp is packed in 16 bits */
		if (bpp == 12)
			bpp = 16;
		def_size = def_vxres * def_vyres * bpp / 8;
		fbdev->mem_desc.region_cnt = 1;
		fbdev->mem_desc.region[0].size = PAGE_ALIGN(def_size);
	}
	r = fbdev->ctrl->init(fbdev, 0, &fbdev->mem_desc);
	if (r < 0) {
		dev_err(fbdev->dev, "controller initialization failed (%d)\n",
			r);
		return r;
	}

#ifdef DEBUG
	for (i = 0; i < fbdev->mem_desc.region_cnt; i++) {
		dev_dbg(fbdev->dev, "region%d phys %08x virt %p size=%lu\n",
			 i,
			 fbdev->mem_desc.region[i].paddr,
			 fbdev->mem_desc.region[i].vaddr,
			 fbdev->mem_desc.region[i].size);
	}
#endif
	return 0;
}