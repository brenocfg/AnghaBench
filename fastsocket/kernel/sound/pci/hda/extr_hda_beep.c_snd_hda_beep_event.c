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
struct input_dev {int dummy; } ;
struct hda_beep {int /*<<< orphan*/  beep_work; int /*<<< orphan*/  tone; int /*<<< orphan*/  linear_tone; } ;

/* Variables and functions */
#define  SND_BELL 129 
#define  SND_TONE 128 
 int /*<<< orphan*/  beep_linear_tone (struct hda_beep*,int) ; 
 int /*<<< orphan*/  beep_standard_tone (struct hda_beep*,int) ; 
 struct hda_beep* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_hda_beep_event(struct input_dev *dev, unsigned int type,
				unsigned int code, int hz)
{
	struct hda_beep *beep = input_get_drvdata(dev);

	switch (code) {
	case SND_BELL:
		if (hz)
			hz = 1000;
	case SND_TONE:
		if (beep->linear_tone)
			beep->tone = beep_linear_tone(beep, hz);
		else
			beep->tone = beep_standard_tone(beep, hz);
		break;
	default:
		return -1;
	}

	/* schedule beep event */
	schedule_work(&beep->beep_work);
	return 0;
}