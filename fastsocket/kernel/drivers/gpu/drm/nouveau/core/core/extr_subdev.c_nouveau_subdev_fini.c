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
struct nouveau_subdev {int unit; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int nouveau_object_fini (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nv_mask (struct nouveau_subdev*,int,int,int) ; 

int
nouveau_subdev_fini(struct nouveau_subdev *subdev, bool suspend)
{
	if (subdev->unit) {
		nv_mask(subdev, 0x000200, subdev->unit, 0x00000000);
		nv_mask(subdev, 0x000200, subdev->unit, subdev->unit);
	}

	return nouveau_object_fini(&subdev->base, suspend);
}