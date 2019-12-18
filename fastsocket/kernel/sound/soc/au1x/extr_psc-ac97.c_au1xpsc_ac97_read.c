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
struct au1xpsc_audio_data {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_CDC (struct au1xpsc_audio_data*) ; 
 int /*<<< orphan*/  AC97_EVNT (struct au1xpsc_audio_data*) ; 
 unsigned short AC97_RW_RETRIES ; 
 int PSC_AC97CDC_INDX (unsigned short) ; 
 int PSC_AC97CDC_RD ; 
 int PSC_AC97EVNT_CD ; 
 struct au1xpsc_audio_data* au1xpsc_ac97_workdata ; 
 int au_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au_sync () ; 
 int /*<<< orphan*/  au_writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static unsigned short au1xpsc_ac97_read(struct snd_ac97 *ac97,
					unsigned short reg)
{
	/* FIXME */
	struct au1xpsc_audio_data *pscdata = au1xpsc_ac97_workdata;
	unsigned short data, retry, tmo;

	au_writel(PSC_AC97EVNT_CD, AC97_EVNT(pscdata));
	au_sync();

	retry = AC97_RW_RETRIES;
	do {
		mutex_lock(&pscdata->lock);

		au_writel(PSC_AC97CDC_RD | PSC_AC97CDC_INDX(reg),
			  AC97_CDC(pscdata));
		au_sync();

		tmo = 2000;
		while ((!(au_readl(AC97_EVNT(pscdata)) & PSC_AC97EVNT_CD))
			&& --tmo)
			udelay(2);

		data = au_readl(AC97_CDC(pscdata)) & 0xffff;

		au_writel(PSC_AC97EVNT_CD, AC97_EVNT(pscdata));
		au_sync();

		mutex_unlock(&pscdata->lock);
	} while (--retry && !tmo);

	return retry ? data : 0xffff;
}