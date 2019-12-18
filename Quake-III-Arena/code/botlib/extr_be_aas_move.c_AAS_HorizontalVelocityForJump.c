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
typedef  float* vec3_t ;
struct TYPE_2__ {float phys_gravity; float phys_maxvelocity; } ;

/* Variables and functions */
 int /*<<< orphan*/  VectorSubtract (float*,float*,float*) ; 
 TYPE_1__ aassettings ; 
 float sqrt (float) ; 

int AAS_HorizontalVelocityForJump(float zvel, vec3_t start, vec3_t end, float *velocity)
{
	float phys_gravity, phys_maxvelocity;
	float maxjump, height2fall, t, top;
	vec3_t dir;

	phys_gravity = aassettings.phys_gravity;
	phys_maxvelocity = aassettings.phys_maxvelocity;

	//maximum height a player can jump with the given initial z velocity
	maxjump = 0.5 * phys_gravity * (zvel / phys_gravity) * (zvel / phys_gravity);
	//top of the parabolic jump
	top = start[2] + maxjump;
	//height the bot will fall from the top
	height2fall = top - end[2];
	//if the goal is to high to jump to
	if (height2fall < 0)
	{
		*velocity = phys_maxvelocity;
		return 0;
	} //end if
	//time a player takes to fall the height
	t = sqrt(height2fall / (0.5 * phys_gravity));
  	//direction from start to end
	VectorSubtract(end, start, dir);
	//
	if ( (t + zvel / phys_gravity) == 0.0f ) {
		*velocity = phys_maxvelocity;
		return 0;
	}
	//calculate horizontal speed
	*velocity = sqrt(dir[0]*dir[0] + dir[1]*dir[1]) / (t + zvel / phys_gravity);
	//the horizontal speed must be lower than the max speed
	if (*velocity > phys_maxvelocity)
	{
		*velocity = phys_maxvelocity;
		return 0;
	} //end if
	return 1;
}