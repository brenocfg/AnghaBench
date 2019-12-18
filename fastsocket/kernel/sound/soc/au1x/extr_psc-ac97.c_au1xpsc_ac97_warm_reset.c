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
struct snd_ac97 {int dummy; } ;
struct au1xpsc_audio_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_RST (struct au1xpsc_audio_data*) ; 
 int /*<<< orphan*/  PSC_AC97RST_SNC ; 
 struct au1xpsc_audio_data* au1xpsc_ac97_workdata ; 
 int /*<<< orphan*/  au_sync () ; 
 int /*<<< orphan*/  au_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void au1xpsc_ac97_warm_reset(struct snd_ac97 *ac97)
{
	/* FIXME */
	struct au1xpsc_audio_data *pscdata = au1xpsc_ac97_workdata;

	au_writel(PSC_AC97RST_SNC, AC97_RST(pscdata));
	au_sync();
	msleep(10);
	au_writel(0, AC97_RST(pscdata));
	au_sync();
}