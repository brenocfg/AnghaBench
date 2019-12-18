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
struct nouveau_subdev {int /*<<< orphan*/  base; } ;
struct TYPE_2__ {int /*<<< orphan*/ ** subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_object_destroy (int /*<<< orphan*/ *) ; 
 TYPE_1__* nv_device (struct nouveau_subdev*) ; 
 int nv_hclass (struct nouveau_subdev*) ; 

void
nouveau_subdev_destroy(struct nouveau_subdev *subdev)
{
	int subidx = nv_hclass(subdev) & 0xff;
	nv_device(subdev)->subdev[subidx] = NULL;
	nouveau_object_destroy(&subdev->base);
}