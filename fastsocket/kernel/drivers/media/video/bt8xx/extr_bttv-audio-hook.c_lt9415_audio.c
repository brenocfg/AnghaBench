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
struct v4l2_tuner {int audmode; } ;
struct bttv {int dummy; } ;

/* Variables and functions */
 int V4L2_TUNER_MODE_LANG1 ; 
 int V4L2_TUNER_MODE_LANG2 ; 
 int V4L2_TUNER_MODE_MONO ; 
 int V4L2_TUNER_MODE_STEREO ; 
 scalar_t__ bttv_gpio ; 
 int /*<<< orphan*/  bttv_gpio_tracking (struct bttv*,char*) ; 
 int /*<<< orphan*/  gpio_bits (int,int) ; 
 int gpio_read () ; 

void lt9415_audio(struct bttv *btv, struct v4l2_tuner *t, int set)
{
	int val = 0;

	if (gpio_read() & 0x4000) {
		t->audmode = V4L2_TUNER_MODE_MONO;
		return;
	}

	if (set) {
		if (t->audmode & V4L2_TUNER_MODE_LANG2)  /* A2 SAP */
			val = 0x0080;
		if (t->audmode & V4L2_TUNER_MODE_STEREO) /* A2 stereo */
			val = 0x0880;
		if ((t->audmode & V4L2_TUNER_MODE_LANG1) ||
		    (t->audmode & V4L2_TUNER_MODE_MONO))
			val = 0;
		gpio_bits(0x0880, val);
		if (bttv_gpio)
			bttv_gpio_tracking(btv,"lt9415");
	} else {
		/* autodetect doesn't work with this card :-( */
		t->audmode = V4L2_TUNER_MODE_MONO | V4L2_TUNER_MODE_STEREO |
			V4L2_TUNER_MODE_LANG1 | V4L2_TUNER_MODE_LANG2;
		return;
	}
}