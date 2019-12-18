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
struct sm501fb_info {int /*<<< orphan*/  regs_res; int /*<<< orphan*/  regs; int /*<<< orphan*/  fbmem_res; int /*<<< orphan*/  fbmem; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  SM501_GATE_DISPLAY ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_resource (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sm501_unit_power (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sm501fb_stop(struct sm501fb_info *info)
{
	/* disable display controller */
	sm501_unit_power(info->dev->parent, SM501_GATE_DISPLAY, 0);

	iounmap(info->fbmem);
	release_resource(info->fbmem_res);
	kfree(info->fbmem_res);

	iounmap(info->regs);
	release_resource(info->regs_res);
	kfree(info->regs_res);
}