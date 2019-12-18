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
typedef  scalar_t__ clock_t ;

/* Variables and functions */
 scalar_t__ CLOCKS_PER_SEC ; 
 scalar_t__ clock () ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int time_blitter( void )
{
	int const duration = 4; /* seconds */
	static clock_t end_time;
	static int count;
	if ( !count )
	{
		clock_t time = clock();
		while ( clock() == time ) { }
		if ( clock() - time > CLOCKS_PER_SEC )
		{
			/* clock increments less-often than once every second */
			printf( "Insufficient time resolution\n" );
			return 0;
		}
		end_time = clock() + CLOCKS_PER_SEC * duration;
	}
	else if ( clock() >= end_time )
	{
		int rate = count / duration;
		printf( "Performance: %d frames per second, which would use %d%% CPU at 60 FPS\n",
				rate, 60 * 100 / rate );
		return 0;
	}
	count++;
	
	return 1;
}