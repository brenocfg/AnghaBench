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
struct tmio_nand {int /*<<< orphan*/  ccr; int /*<<< orphan*/  fcr; scalar_t__ irq; int /*<<< orphan*/  mtd; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,struct tmio_nand*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct tmio_nand*) ; 
 int /*<<< orphan*/  nand_release (int /*<<< orphan*/ *) ; 
 struct tmio_nand* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  tmio_hw_stop (struct platform_device*,struct tmio_nand*) ; 

__attribute__((used)) static int tmio_remove(struct platform_device *dev)
{
	struct tmio_nand *tmio = platform_get_drvdata(dev);

	nand_release(&tmio->mtd);
	if (tmio->irq)
		free_irq(tmio->irq, tmio);
	tmio_hw_stop(dev, tmio);
	iounmap(tmio->fcr);
	iounmap(tmio->ccr);
	kfree(tmio);
	return 0;
}