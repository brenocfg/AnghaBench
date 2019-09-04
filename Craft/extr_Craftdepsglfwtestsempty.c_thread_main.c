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
struct timespec {int tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  glfwPostEmptyEvent () ; 
 scalar_t__ running ; 
 int /*<<< orphan*/  thrd_sleep (struct timespec*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int thread_main(void* data)
{
    struct timespec time;

    while (running)
    {
        clock_gettime(CLOCK_REALTIME, &time);
        time.tv_sec += 1;
        thrd_sleep(&time, NULL);

        glfwPostEmptyEvent();
    }

    return 0;
}