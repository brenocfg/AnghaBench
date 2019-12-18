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
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct mca_device {TYPE_1__ dev; } ;
struct TYPE_4__ {void* (* mca_transform_memory ) (struct mca_device*,void*) ;} ;
struct mca_bus {TYPE_2__ f; } ;

/* Variables and functions */
 void* stub1 (struct mca_device*,void*) ; 
 struct mca_bus* to_mca_bus (int /*<<< orphan*/ ) ; 

void *mca_device_transform_memory(struct mca_device *mca_dev, void *mem)
{
	struct mca_bus *mca_bus = to_mca_bus(mca_dev->dev.parent);

	return mca_bus->f.mca_transform_memory(mca_dev, mem);
}