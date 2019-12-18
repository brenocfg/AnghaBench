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
struct nouveau_subdev {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int nouveau_object_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_subdev_reset (int /*<<< orphan*/ *) ; 

int
nouveau_subdev_init(struct nouveau_subdev *subdev)
{
	int ret = nouveau_object_init(&subdev->base);
	if (ret)
		return ret;

	nouveau_subdev_reset(&subdev->base);
	return 0;
}