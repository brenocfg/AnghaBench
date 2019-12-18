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
struct ngene {struct ngene* vin_buf; struct ngene* ain_buf; struct ngene* tsout_buf; scalar_t__ iomem; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_common_buffers (struct ngene*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  vfree (struct ngene*) ; 

__attribute__((used)) static void ngene_release_buffers(struct ngene *dev)
{
	if (dev->iomem)
		iounmap(dev->iomem);
	free_common_buffers(dev);
	vfree(dev->tsout_buf);
	vfree(dev->ain_buf);
	vfree(dev->vin_buf);
	vfree(dev);
}