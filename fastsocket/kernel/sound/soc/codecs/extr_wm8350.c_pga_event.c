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
struct wm8350_output {int active; int /*<<< orphan*/  ramp; } ;
struct wm8350_data {struct wm8350_output out2; struct wm8350_output out1; } ;
struct snd_soc_dapm_widget {int shift; struct snd_soc_codec* codec; } ;
struct snd_soc_codec {int /*<<< orphan*/  delayed_work; struct wm8350_data* private_data; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  SND_SOC_DAPM_POST_PMU 129 
#define  SND_SOC_DAPM_PRE_PMD 128 
 int /*<<< orphan*/  WM8350_RAMP_DOWN ; 
 int /*<<< orphan*/  WM8350_RAMP_UP ; 
 int /*<<< orphan*/  delayed_work_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pga_event(struct snd_soc_dapm_widget *w,
		     struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;
	struct wm8350_data *wm8350_data = codec->private_data;
	struct wm8350_output *out;

	switch (w->shift) {
	case 0:
	case 1:
		out = &wm8350_data->out1;
		break;
	case 2:
	case 3:
		out = &wm8350_data->out2;
		break;

	default:
		BUG();
		return -1;
	}

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		out->ramp = WM8350_RAMP_UP;
		out->active = 1;

		if (!delayed_work_pending(&codec->delayed_work))
			schedule_delayed_work(&codec->delayed_work,
					      msecs_to_jiffies(1));
		break;

	case SND_SOC_DAPM_PRE_PMD:
		out->ramp = WM8350_RAMP_DOWN;
		out->active = 0;

		if (!delayed_work_pending(&codec->delayed_work))
			schedule_delayed_work(&codec->delayed_work,
					      msecs_to_jiffies(1));
		break;
	}

	return 0;
}