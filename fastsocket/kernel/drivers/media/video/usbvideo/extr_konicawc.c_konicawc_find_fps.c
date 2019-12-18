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

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int,char*,int,int,...) ; 
 size_t MAX_SPEED ; 
 int** spd_to_fps ; 

__attribute__((used)) static int konicawc_find_fps(int size, int fps)
{
	int i;

	fps *= 3;
	DEBUG(1, "konica_find_fps: size = %d fps = %d", size, fps);
	if(fps <= spd_to_fps[size][0])
		return 0;

	if(fps >= spd_to_fps[size][MAX_SPEED])
		return MAX_SPEED;

	for(i = 0; i < MAX_SPEED; i++) {
		if((fps >= spd_to_fps[size][i]) && (fps <= spd_to_fps[size][i+1])) {
			DEBUG(2, "fps %d between %d and %d", fps, i, i+1);
			if( (fps - spd_to_fps[size][i]) < (spd_to_fps[size][i+1] - fps))
				return i;
			else
				return i+1;
		}
	}
	return MAX_SPEED+1;
}