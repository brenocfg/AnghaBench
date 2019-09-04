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
struct timespec {long tv_nsec; double tv_sec; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  emscripten_thread_sleep (double) ; 

int nanosleep(const struct timespec *req, struct timespec *rem)
{
	if (!req || req->tv_nsec < 0 || req->tv_nsec > 999999999L || req->tv_sec < 0) return EINVAL;
	emscripten_thread_sleep(req->tv_sec * 1000.0 + req->tv_nsec / 1e6);
	return 0;
}