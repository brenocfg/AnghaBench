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
struct TYPE_2__ {int /*<<< orphan*/ * bus; } ;
struct bttv_sub_driver {TYPE_1__ drv; int /*<<< orphan*/  wanted; } ;

/* Variables and functions */
 int /*<<< orphan*/  bttv_sub_bus_type ; 
 int driver_register (TYPE_1__*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 

int bttv_sub_register(struct bttv_sub_driver *sub, char *wanted)
{
	sub->drv.bus = &bttv_sub_bus_type;
	snprintf(sub->wanted,sizeof(sub->wanted),"%s",wanted);
	return driver_register(&sub->drv);
}