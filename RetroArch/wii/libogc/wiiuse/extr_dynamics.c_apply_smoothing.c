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
struct orient_t {float roll; int a_roll; float pitch; int a_pitch; } ;
struct accel_t {float st_roll; int st_alpha; float st_pitch; } ;

/* Variables and functions */
#define  SMOOTH_PITCH 129 
#define  SMOOTH_ROLL 128 
 int /*<<< orphan*/  isinf (float) ; 
 int /*<<< orphan*/  isnan (float) ; 

void apply_smoothing(struct accel_t* ac, struct orient_t* orient, int type) {
	switch (type) {
		case SMOOTH_ROLL:
		{
			/* it's possible last iteration was nan or inf, so set it to 0 if that happened */
			if (isnan(ac->st_roll) || isinf(ac->st_roll))
				ac->st_roll = 0.0f;

			/*
			 *	If the sign changes (which will happen if going from -180 to 180)
			 *	or from (-1 to 1) then don't smooth, just use the new angle.
			 */
			if (((ac->st_roll < 0) && (orient->roll > 0)) || ((ac->st_roll > 0) && (orient->roll < 0))) {
				ac->st_roll = orient->roll;
			} else {
				orient->roll = ac->st_roll + (ac->st_alpha * (orient->a_roll - ac->st_roll));
				ac->st_roll = orient->roll;
			}

			return;
		}

		case SMOOTH_PITCH:
		{
			if (isnan(ac->st_pitch) || isinf(ac->st_pitch))
				ac->st_pitch = 0.0f;

			if (((ac->st_pitch < 0) && (orient->pitch > 0)) || ((ac->st_pitch > 0) && (orient->pitch < 0))) {
				ac->st_pitch = orient->pitch;
			} else {
				orient->pitch = ac->st_pitch + (ac->st_alpha * (orient->a_pitch - ac->st_pitch));
				ac->st_pitch = orient->pitch;
			}

			return;
		}
	}
}