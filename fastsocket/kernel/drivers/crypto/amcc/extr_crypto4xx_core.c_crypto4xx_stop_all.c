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
struct crypto4xx_core_device {struct crypto4xx_core_device* dev; int /*<<< orphan*/  ce_base; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto4xx_destroy_gdr (struct crypto4xx_core_device*) ; 
 int /*<<< orphan*/  crypto4xx_destroy_pdr (struct crypto4xx_core_device*) ; 
 int /*<<< orphan*/  crypto4xx_destroy_sdr (struct crypto4xx_core_device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct crypto4xx_core_device*) ; 

__attribute__((used)) static void crypto4xx_stop_all(struct crypto4xx_core_device *core_dev)
{
	crypto4xx_destroy_pdr(core_dev->dev);
	crypto4xx_destroy_gdr(core_dev->dev);
	crypto4xx_destroy_sdr(core_dev->dev);
	dev_set_drvdata(core_dev->device, NULL);
	iounmap(core_dev->dev->ce_base);
	kfree(core_dev->dev);
	kfree(core_dev);
}