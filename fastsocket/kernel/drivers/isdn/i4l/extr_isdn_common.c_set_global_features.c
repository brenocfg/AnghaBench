#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__** drv; int /*<<< orphan*/  global_features; } ;
struct TYPE_5__ {TYPE_1__* interface; } ;
struct TYPE_4__ {int /*<<< orphan*/  features; } ;

/* Variables and functions */
 int ISDN_MAX_DRIVERS ; 
 TYPE_3__* dev ; 

__attribute__((used)) static void
set_global_features(void)
{
	int drvidx;

	dev->global_features = 0;
	for (drvidx = 0; drvidx < ISDN_MAX_DRIVERS; drvidx++) {
		if (!dev->drv[drvidx])
			continue;
		if (dev->drv[drvidx]->interface)
			dev->global_features |= dev->drv[drvidx]->interface->features;
	}
}