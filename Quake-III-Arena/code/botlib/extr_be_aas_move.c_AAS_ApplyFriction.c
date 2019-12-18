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
typedef  float* vec3_t ;

/* Variables and functions */
 float sqrt (float) ; 

void AAS_ApplyFriction(vec3_t vel, float friction, float stopspeed,
													float frametime)
{
	float speed, control, newspeed;

	//horizontal speed
	speed = sqrt(vel[0] * vel[0] + vel[1] * vel[1]);
	if (speed)
	{
		control = speed < stopspeed ? stopspeed : speed;
		newspeed = speed - frametime * control * friction;
		if (newspeed < 0) newspeed = 0;
		newspeed /= speed;
		vel[0] *= newspeed;
		vel[1] *= newspeed;
	} //end if
}