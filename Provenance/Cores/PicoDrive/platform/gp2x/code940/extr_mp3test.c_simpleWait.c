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
struct timeval {int tv_sec; int tv_usec; } ;

/* Variables and functions */
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spend_cycles (int) ; 

__attribute__((used)) static void simpleWait(int thissec, int lim_time)
{
	struct timeval tval;

	spend_cycles(1024);
	gettimeofday(&tval, 0);
	if(thissec != tval.tv_sec) tval.tv_usec+=1000000;

	while(tval.tv_usec < lim_time)
	{
		spend_cycles(1024);
		gettimeofday(&tval, 0);
		if(thissec != tval.tv_sec) tval.tv_usec+=1000000;
	}
}