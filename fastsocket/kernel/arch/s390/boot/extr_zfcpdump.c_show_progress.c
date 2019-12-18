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
struct timeval {int tv_sec; } ;
struct TYPE_2__ {int last_progress; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRINT (char*,unsigned long long,unsigned long long,double) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 TYPE_1__ g ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void show_progress(unsigned long long written, unsigned long long max)
{
	int    time;
	struct timeval t;
	double percent;

	gettimeofday(&t, NULL);
	time = t.tv_sec;
	if ((time < g.last_progress) && (written != max) && (written != 0))
		return;
	g.last_progress = time + 10;
	percent = ((double) written / (double) max) * 100.0;
	PRINT(" %4lli MB of %4lli MB (%5.1f%% )\n", written >> 20, max >> 20,
		percent);
	fflush(stdout);
}