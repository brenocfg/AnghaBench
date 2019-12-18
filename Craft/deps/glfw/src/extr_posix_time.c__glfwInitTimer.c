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
struct timespec {int dummy; } ;
struct TYPE_3__ {int resolution; int /*<<< orphan*/  base; int /*<<< orphan*/  monotonic; } ;
struct TYPE_4__ {TYPE_1__ posix_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  GL_TRUE ; 
 TYPE_2__ _glfw ; 
 scalar_t__ clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  getRawTime () ; 

void _glfwInitTimer(void)
{
#if defined(CLOCK_MONOTONIC)
    struct timespec ts;

    if (clock_gettime(CLOCK_MONOTONIC, &ts) == 0)
    {
        _glfw.posix_time.monotonic = GL_TRUE;
        _glfw.posix_time.resolution = 1e-9;
    }
    else
#endif
    {
        _glfw.posix_time.resolution = 1e-6;
    }

    _glfw.posix_time.base = getRawTime();
}