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
struct of_device {int /*<<< orphan*/  node; } ;
struct TYPE_4__ {int /*<<< orphan*/  fccp; } ;
struct TYPE_3__ {int /*<<< orphan*/  fecp; } ;
struct fs_enet_private {TYPE_2__ fcc; TYPE_1__ fec; int /*<<< orphan*/  interrupt; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NO_IRQ ; 
 int /*<<< orphan*/  of_iomap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_irq_to_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct of_device* to_of_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_pd_setup(struct fs_enet_private *fep)
{
	struct of_device *ofdev = to_of_device(fep->dev);

	fep->interrupt = of_irq_to_resource(ofdev->node, 0, NULL);
	if (fep->interrupt == NO_IRQ)
		return -EINVAL;

	fep->fec.fecp = of_iomap(ofdev->node, 0);
	if (!fep->fcc.fccp)
		return -EINVAL;

	return 0;
}