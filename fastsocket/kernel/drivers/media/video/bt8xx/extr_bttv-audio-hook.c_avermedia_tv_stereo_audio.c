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
 int /*<<< orphan*/  BT848_GPIO_DATA ; 
 int V4L2_TUNER_MODE_LANG1 ; 
 int V4L2_TUNER_MODE_LANG2 ; 
 int V4L2_TUNER_MODE_MONO ; 
 int V4L2_TUNER_MODE_STEREO ; 
 int /*<<< orphan*/  btaor (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ bttv_gpio ; 
 int /*<<< orphan*/  bttv_gpio_tracking (struct bttv*,char*) ; 

void avermedia_tv_stereo_audio(struct bttv *btv, struct v4l2_tuner *t, int set)
{
	int val = 0;

	if (set) {
		if (t->audmode & V4L2_TUNER_MODE_LANG2)   /* SAP */
			val = 0x01;
		if (t->audmode & V4L2_TUNER_MODE_STEREO)  /* STEREO */
			val = 0x02;
		btaor(val, ~0x03, BT848_GPIO_DATA);
		if (bttv_gpio)
			bttv_gpio_tracking(btv,"avermedia");
	} else {
		t->audmode = V4L2_TUNER_MODE_MONO | V4L2_TUNER_MODE_STEREO |
			V4L2_TUNER_MODE_LANG1 | V4L2_TUNER_MODE_LANG2;
		return;
	}
}