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
struct v4l2_subdev {int dummy; } ;
struct CHIPSTATE {struct v4l2_subdev sd; } ;

/* Variables and functions */
 int TDA9840_DS_DUAL ; 
 int TDA9840_ST_STEREO ; 
 int V4L2_TUNER_MODE_LANG1 ; 
 int V4L2_TUNER_MODE_LANG2 ; 
 int V4L2_TUNER_MODE_MONO ; 
 int V4L2_TUNER_MODE_STEREO ; 
 int chip_read (struct CHIPSTATE*) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,int,int) ; 

__attribute__((used)) static int tda9840_getmode(struct CHIPSTATE *chip)
{
	struct v4l2_subdev *sd = &chip->sd;
	int val, mode;

	val = chip_read(chip);
	mode = V4L2_TUNER_MODE_MONO;
	if (val & TDA9840_DS_DUAL)
		mode |= V4L2_TUNER_MODE_LANG1 | V4L2_TUNER_MODE_LANG2;
	if (val & TDA9840_ST_STEREO)
		mode |= V4L2_TUNER_MODE_STEREO;

	v4l2_dbg(1, debug, sd, "tda9840_getmode(): raw chip read: %d, return: %d\n",
		val, mode);
	return mode;
}