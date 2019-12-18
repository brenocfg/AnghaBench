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
struct nouveau_bar {int /*<<< orphan*/  base; scalar_t__ iomem; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  nouveau_subdev_destroy (int /*<<< orphan*/ *) ; 

void
nouveau_bar_destroy(struct nouveau_bar *bar)
{
	if (bar->iomem)
		iounmap(bar->iomem);
	nouveau_subdev_destroy(&bar->base);
}