#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dai {int dummy; } ;
struct platform_device {int dummy; } ;
struct TYPE_6__ {struct TYPE_6__* ioarea; int /*<<< orphan*/  mmio; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2S_CFG (TYPE_1__*) ; 
 int /*<<< orphan*/  PSC_CTRL (TYPE_1__*) ; 
 int /*<<< orphan*/  PSC_CTRL_DISABLE ; 
 TYPE_1__* au1xpsc_i2s_workdata ; 
 int /*<<< orphan*/  au_sync () ; 
 int /*<<< orphan*/  au_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  release_resource (TYPE_1__*) ; 

__attribute__((used)) static void au1xpsc_i2s_remove(struct platform_device *pdev,
			       struct snd_soc_dai *dai)
{
	au_writel(0, I2S_CFG(au1xpsc_i2s_workdata));
	au_sync();
	au_writel(PSC_CTRL_DISABLE, PSC_CTRL(au1xpsc_i2s_workdata));
	au_sync();

	iounmap(au1xpsc_i2s_workdata->mmio);
	release_resource(au1xpsc_i2s_workdata->ioarea);
	kfree(au1xpsc_i2s_workdata->ioarea);
	kfree(au1xpsc_i2s_workdata);
	au1xpsc_i2s_workdata = NULL;
}