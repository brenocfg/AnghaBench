#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct TYPE_3__ {void* dev_flags; void* dev_devwidth; void* dev_tsize; scalar_t__ dev_intpolarity; scalar_t__ dev_intlevel; void* dev_physaddr; void* dev_id; } ;
typedef  TYPE_1__ dbdev_tab_t ;

/* Variables and functions */
 scalar_t__ IDE_PHYS_ADDR ; 

__attribute__((used)) static void auide_init_dbdma_dev(dbdev_tab_t *dev, u32 dev_id, u32 tsize, u32 devwidth, u32 flags)
{
	dev->dev_id          = dev_id;
	dev->dev_physaddr    = (u32)IDE_PHYS_ADDR;
	dev->dev_intlevel    = 0;
	dev->dev_intpolarity = 0;
	dev->dev_tsize       = tsize;
	dev->dev_devwidth    = devwidth;
	dev->dev_flags       = flags;
}