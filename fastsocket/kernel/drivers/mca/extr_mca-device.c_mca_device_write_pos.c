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
struct TYPE_4__ {int /*<<< orphan*/  (* mca_write_pos ) (struct mca_device*,int,unsigned char) ;} ;
struct mca_bus {TYPE_2__ f; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct mca_device*,int,unsigned char) ; 
 struct mca_bus* to_mca_bus (int /*<<< orphan*/ ) ; 

void mca_device_write_pos(struct mca_device *mca_dev, int reg,
			  unsigned char byte)
{
	struct mca_bus *mca_bus = to_mca_bus(mca_dev->dev.parent);

	mca_bus->f.mca_write_pos(mca_dev, reg, byte);
}