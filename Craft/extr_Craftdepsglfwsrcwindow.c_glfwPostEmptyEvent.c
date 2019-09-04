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
struct TYPE_2__ {int /*<<< orphan*/  windowListHead; } ;

/* Variables and functions */
 int /*<<< orphan*/  _GLFW_REQUIRE_INIT () ; 
 TYPE_1__ _glfw ; 
 int /*<<< orphan*/  _glfwPlatformPostEmptyEvent () ; 

void glfwPostEmptyEvent(void)
{
    _GLFW_REQUIRE_INIT();

    if (!_glfw.windowListHead)
        return;

    _glfwPlatformPostEmptyEvent();
}