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
typedef  int u32 ;
struct timespec {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;

/* Variables and functions */
 int TB_NSPERSEC ; 

void timespec_subtract(const struct timespec *tp_start,const struct timespec *tp_end,struct timespec *result)
{
	struct timespec start_st = *tp_start;
	struct timespec *start = &start_st;
	u32 nsecpersec = TB_NSPERSEC;

	if(tp_end->tv_nsec<start->tv_nsec) {
		int secs = (start->tv_nsec - tp_end->tv_nsec)/nsecpersec+1;
		start->tv_nsec -= nsecpersec * secs;
		start->tv_sec += secs;
	}
	if((tp_end->tv_nsec - start->tv_nsec)>nsecpersec) {
		int secs = (start->tv_nsec - tp_end->tv_nsec)/nsecpersec;
		start->tv_nsec += nsecpersec * secs;
		start->tv_sec -= secs;
	}

	result->tv_sec = (tp_end->tv_sec - start->tv_sec);
	result->tv_nsec = (tp_end->tv_nsec - start->tv_nsec);
}