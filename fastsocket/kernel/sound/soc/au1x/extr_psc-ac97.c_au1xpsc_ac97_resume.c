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
struct snd_soc_dai {int dummy; } ;
struct TYPE_3__ {int* pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSC_SEL (TYPE_1__*) ; 
 int PSC_SEL_PS_AC97MODE ; 
 TYPE_1__* au1xpsc_ac97_workdata ; 
 int /*<<< orphan*/  au_sync () ; 
 int /*<<< orphan*/  au_writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int au1xpsc_ac97_resume(struct snd_soc_dai *dai)
{
	/* restore PSC clock config */
	au_writel(au1xpsc_ac97_workdata->pm[0] | PSC_SEL_PS_AC97MODE,
			PSC_SEL(au1xpsc_ac97_workdata));
	au_sync();

	/* after this point the ac97 core will cold-reset the codec.
	 * During cold-reset the PSC is reinitialized and the last
	 * configuration set up in hw_params() is restored.
	 */
	return 0;
}