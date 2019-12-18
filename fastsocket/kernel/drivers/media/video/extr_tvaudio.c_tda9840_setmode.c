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
struct TYPE_2__ {int* bytes; } ;
struct CHIPSTATE {TYPE_1__ shadow; } ;

/* Variables and functions */
 int TDA9840_DUALA ; 
 int TDA9840_DUALB ; 
 int TDA9840_MONO ; 
 int TDA9840_STEREO ; 
 int TDA9840_SW ; 
#define  V4L2_TUNER_MODE_LANG1 131 
#define  V4L2_TUNER_MODE_LANG2 130 
#define  V4L2_TUNER_MODE_MONO 129 
#define  V4L2_TUNER_MODE_STEREO 128 
 int /*<<< orphan*/  chip_write (struct CHIPSTATE*,int,int) ; 

__attribute__((used)) static void tda9840_setmode(struct CHIPSTATE *chip, int mode)
{
	int update = 1;
	int t = chip->shadow.bytes[TDA9840_SW + 1] & ~0x7e;

	switch (mode) {
	case V4L2_TUNER_MODE_MONO:
		t |= TDA9840_MONO;
		break;
	case V4L2_TUNER_MODE_STEREO:
		t |= TDA9840_STEREO;
		break;
	case V4L2_TUNER_MODE_LANG1:
		t |= TDA9840_DUALA;
		break;
	case V4L2_TUNER_MODE_LANG2:
		t |= TDA9840_DUALB;
		break;
	default:
		update = 0;
	}

	if (update)
		chip_write(chip, TDA9840_SW, t);
}