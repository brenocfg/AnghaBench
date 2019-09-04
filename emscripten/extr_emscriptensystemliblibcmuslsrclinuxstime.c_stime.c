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
typedef  int /*<<< orphan*/  time_t ;
struct timeval {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  const tv_sec; } ;

/* Variables and functions */
 int settimeofday (struct timeval*,void*) ; 

int stime(const time_t *t)
{
	struct timeval tv = { .tv_sec = *t, .tv_usec = 0 };
	return settimeofday(&tv, (void *)0);
}