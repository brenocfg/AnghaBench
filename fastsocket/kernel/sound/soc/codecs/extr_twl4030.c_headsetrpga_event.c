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
struct twl4030_priv {int hsr_enabled; int /*<<< orphan*/  hsl_enabled; } ;
struct snd_soc_dapm_widget {TYPE_1__* codec; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_2__ {struct twl4030_priv* private_data; } ;

/* Variables and functions */
#define  SND_SOC_DAPM_POST_PMD 129 
#define  SND_SOC_DAPM_POST_PMU 128 
 int /*<<< orphan*/  headset_ramp (TYPE_1__*,int) ; 

__attribute__((used)) static int headsetrpga_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct twl4030_priv *twl4030 = w->codec->private_data;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		/* Do the ramp-up only once */
		if (!twl4030->hsl_enabled)
			headset_ramp(w->codec, 1);

		twl4030->hsr_enabled = 1;
		break;
	case SND_SOC_DAPM_POST_PMD:
		/* Do the ramp-down only if both headsetL/R is disabled */
		if (!twl4030->hsl_enabled)
			headset_ramp(w->codec, 0);

		twl4030->hsr_enabled = 0;
		break;
	}
	return 0;
}