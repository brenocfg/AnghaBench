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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ S_OK ; 
 scalar_t__ _glfw_DwmIsCompositionEnabled (int /*<<< orphan*/ *) ; 

BOOL _glfwIsCompositionEnabled(void)
{
    BOOL enabled;

    if (!_glfw_DwmIsCompositionEnabled)
        return FALSE;

    if (_glfw_DwmIsCompositionEnabled(&enabled) != S_OK)
        return FALSE;

    return enabled;
}