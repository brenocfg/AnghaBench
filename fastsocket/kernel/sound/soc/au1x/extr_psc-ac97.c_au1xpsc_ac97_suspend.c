#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dai {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_CFG (TYPE_1__*) ; 
 int /*<<< orphan*/  PSC_CTRL (TYPE_1__*) ; 
 int /*<<< orphan*/  PSC_CTRL_DISABLE ; 
 int /*<<< orphan*/  PSC_SEL (TYPE_1__*) ; 
 TYPE_1__* au1xpsc_ac97_workdata ; 
 int /*<<< orphan*/  au_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au_sync () ; 
 int /*<<< orphan*/  au_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int au1xpsc_ac97_suspend(struct snd_soc_dai *dai)
{
	/* save interesting registers and disable PSC */
	au1xpsc_ac97_workdata->pm[0] =
			au_readl(PSC_SEL(au1xpsc_ac97_workdata));

	au_writel(0, AC97_CFG(au1xpsc_ac97_workdata));
	au_sync();
	au_writel(PSC_CTRL_DISABLE, PSC_CTRL(au1xpsc_ac97_workdata));
	au_sync();

	return 0;
}