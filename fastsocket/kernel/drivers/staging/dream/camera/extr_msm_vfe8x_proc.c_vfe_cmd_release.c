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
struct resource {scalar_t__ start; scalar_t__ end; } ;
struct platform_device {int dummy; } ;
struct TYPE_3__ {struct TYPE_3__* extdata; scalar_t__ extlen; int /*<<< orphan*/  vfebase; int /*<<< orphan*/  vfeirq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 TYPE_1__* ctrl ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (scalar_t__,scalar_t__) ; 

void vfe_cmd_release(struct platform_device *dev)
{
	struct resource	*mem;

	disable_irq(ctrl->vfeirq);
	free_irq(ctrl->vfeirq, 0);

	iounmap(ctrl->vfebase);
	mem = platform_get_resource(dev, IORESOURCE_MEM, 0);
	release_mem_region(mem->start, (mem->end - mem->start) + 1);

	ctrl->extlen = 0;

	kfree(ctrl->extdata);
	kfree(ctrl);
}