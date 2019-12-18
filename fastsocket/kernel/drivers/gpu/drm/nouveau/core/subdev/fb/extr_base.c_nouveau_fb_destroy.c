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
struct TYPE_2__ {int regions; int /*<<< orphan*/ * region; int /*<<< orphan*/  (* fini ) (struct nouveau_fb*,int,int /*<<< orphan*/ *) ;} ;
struct nouveau_fb {int /*<<< orphan*/  base; int /*<<< orphan*/  vram; int /*<<< orphan*/  tags; TYPE_1__ tile; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_mm_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_subdev_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct nouveau_fb*,int,int /*<<< orphan*/ *) ; 

void
nouveau_fb_destroy(struct nouveau_fb *pfb)
{
	int i;

	for (i = 0; i < pfb->tile.regions; i++)
		pfb->tile.fini(pfb, i, &pfb->tile.region[i]);
	nouveau_mm_fini(&pfb->tags);
	nouveau_mm_fini(&pfb->vram);

	nouveau_subdev_destroy(&pfb->base);
}