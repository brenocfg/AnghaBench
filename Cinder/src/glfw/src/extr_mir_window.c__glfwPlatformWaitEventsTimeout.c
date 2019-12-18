#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timespec {long tv_sec; long tv_nsec; } ;
struct TYPE_3__ {int /*<<< orphan*/  event_mutex; int /*<<< orphan*/  event_cond; int /*<<< orphan*/  event_queue; } ;
struct TYPE_4__ {TYPE_1__ mir; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 TYPE_2__ _glfw ; 
 int /*<<< orphan*/  _glfwPlatformPollEvents () ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 scalar_t__ emptyEventQueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_cond_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void _glfwPlatformWaitEventsTimeout(double timeout)
{
    pthread_mutex_lock(&_glfw.mir.event_mutex);

    if (emptyEventQueue(_glfw.mir.event_queue))
    {
        struct timespec time;
        clock_gettime(CLOCK_REALTIME, &time);
        time.tv_sec += (long) timeout;
        time.tv_nsec += (long) ((timeout - (long) timeout) * 1e9);
        pthread_cond_timedwait(&_glfw.mir.event_cond, &_glfw.mir.event_mutex, &time);
    }

    pthread_mutex_unlock(&_glfw.mir.event_mutex);

    _glfwPlatformPollEvents();
}