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
struct TYPE_2__ {int regions; int /*<<< orphan*/ * region; int /*<<< orphan*/  (* prog ) (struct nouveau_fb*,int,int /*<<< orphan*/ *) ;} ;
struct nouveau_fb {TYPE_1__ tile; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int nouveau_subdev_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct nouveau_fb*,int,int /*<<< orphan*/ *) ; 

int
nouveau_fb_init(struct nouveau_fb *pfb)
{
	int ret, i;

	ret = nouveau_subdev_init(&pfb->base);
	if (ret)
		return ret;

	for (i = 0; i < pfb->tile.regions; i++)
		pfb->tile.prog(pfb, i, &pfb->tile.region[i]);

	return 0;
}