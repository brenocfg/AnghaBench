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
struct timespec {int tv_nsec; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int /*<<< orphan*/  __clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 

char *__randname(char *template)
{
	int i;
	struct timespec ts;
	unsigned long r;

	__clock_gettime(CLOCK_REALTIME, &ts);
	r = ts.tv_nsec*65537 ^ (uintptr_t)&ts / 16 + (uintptr_t)template;
	for (i=0; i<6; i++, r>>=5)
		template[i] = 'A'+(r&15)+(r&16)*2;

	return template;
}