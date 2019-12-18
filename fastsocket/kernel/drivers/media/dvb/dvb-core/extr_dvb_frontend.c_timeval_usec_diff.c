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
struct timeval {int tv_usec; } ;
typedef  int s32 ;

/* Variables and functions */

s32 timeval_usec_diff(struct timeval lasttime, struct timeval curtime)
{
	return ((curtime.tv_usec < lasttime.tv_usec) ?
		1000000 - lasttime.tv_usec + curtime.tv_usec :
		curtime.tv_usec - lasttime.tv_usec);
}