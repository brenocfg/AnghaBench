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
struct timeval {int tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gp2x_init () ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  spend_cycles (int) ; 

int main(void)
{
	struct timeval tval; // timing
	int thissec = 0, frames_done = 0;

	gp2x_init();

	for (;;)
	{
		gettimeofday(&tval, 0);

		if(thissec != tval.tv_sec)
		{
			thissec = tval.tv_sec;

			printf("frames_done: %i\n", frames_done);
			frames_done = 0;
		}


		//gp2x_video_wait_vsync();
		//usleep(1); // sleeps a minimum of ~20ms
		//gp2x_video_flip(); // can be called ~430000 times/sec
		spend_cycles(1000);
		frames_done++;
	}

}