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
struct bttv {scalar_t__ radio_user; } ;

/* Variables and functions */
 int V4L2_TUNER_MODE_LANG1 ; 
 int V4L2_TUNER_MODE_LANG2 ; 
 int V4L2_TUNER_MODE_MONO ; 
 int V4L2_TUNER_MODE_STEREO ; 
 scalar_t__ bttv_gpio ; 
 int /*<<< orphan*/  bttv_gpio_tracking (struct bttv*,char*) ; 
 int /*<<< orphan*/  gpio_bits (int,unsigned int) ; 

void fv2000s_audio(struct bttv *btv, struct v4l2_tuner *t, int set)
{
	unsigned int val = 0xffff;

	if (btv->radio_user)
		return;

	if (set) {
		if (t->audmode & V4L2_TUNER_MODE_MONO)	{
			val = 0x0000;
		}
		if ((t->audmode & (V4L2_TUNER_MODE_LANG1 | V4L2_TUNER_MODE_LANG2))
		    || (t->audmode & V4L2_TUNER_MODE_STEREO)) {
			val = 0x1080; /*-dk-???: 0x0880, 0x0080, 0x1800 ... */
		}
		if (val != 0xffff) {
			gpio_bits(0x1800, val);
			if (bttv_gpio)
				bttv_gpio_tracking(btv,"fv2000s");
		}
	} else {
		t->audmode = V4L2_TUNER_MODE_MONO | V4L2_TUNER_MODE_STEREO |
			V4L2_TUNER_MODE_LANG1 | V4L2_TUNER_MODE_LANG2;
	}
}