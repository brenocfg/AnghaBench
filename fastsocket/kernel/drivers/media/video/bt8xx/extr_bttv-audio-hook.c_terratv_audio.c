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
 int /*<<< orphan*/  gpio_bits (int,unsigned int) ; 
 int /*<<< orphan*/  gpio_inout (int,int) ; 

void terratv_audio(struct bttv *btv,  struct v4l2_tuner *t, int set)
{
	unsigned int con = 0;

	if (set) {
		gpio_inout(0x180000,0x180000);
		if (t->audmode & V4L2_TUNER_MODE_LANG2)
			con = 0x080000;
		if (t->audmode & V4L2_TUNER_MODE_STEREO)
			con = 0x180000;
		gpio_bits(0x180000, con);
		if (bttv_gpio)
			bttv_gpio_tracking(btv,"terratv");
	} else {
		t->audmode = V4L2_TUNER_MODE_MONO | V4L2_TUNER_MODE_STEREO |
			V4L2_TUNER_MODE_LANG1 | V4L2_TUNER_MODE_LANG2;
	}
}