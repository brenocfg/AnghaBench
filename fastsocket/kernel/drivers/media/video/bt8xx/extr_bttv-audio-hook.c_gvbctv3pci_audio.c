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
 int V4L2_TUNER_MODE_STEREO ; 
 int /*<<< orphan*/  gpio_bits (int,unsigned int) ; 
 int /*<<< orphan*/  gpio_inout (int,int) ; 

void gvbctv3pci_audio(struct bttv *btv, struct v4l2_tuner *t, int set)
{
	unsigned int con = 0;

	if (set) {
		gpio_inout(0x300, 0x300);
		if (t->audmode & V4L2_TUNER_MODE_LANG1)
			con = 0x000;
		if (t->audmode & V4L2_TUNER_MODE_LANG2)
			con = 0x300;
		if (t->audmode & V4L2_TUNER_MODE_STEREO)
			con = 0x200;
/*		if (t->audmode & V4L2_TUNER_MODE_MONO)
 *			con = 0x100; */
		gpio_bits(0x300, con);
	} else {
		t->audmode = V4L2_TUNER_MODE_STEREO |
			  V4L2_TUNER_MODE_LANG1  | V4L2_TUNER_MODE_LANG2;
	}
}