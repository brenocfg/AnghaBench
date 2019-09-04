#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int modeCount; int /*<<< orphan*/ * modes; } ;
typedef  TYPE_1__ _GLFWmonitor ;
typedef  int /*<<< orphan*/  GLFWvidmode ;

/* Variables and functions */
 int GL_FALSE ; 
 int GL_TRUE ; 
 int /*<<< orphan*/ * _glfwPlatformGetVideoModes (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  compareVideoModes ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int refreshVideoModes(_GLFWmonitor* monitor)
{
    int modeCount;
    GLFWvidmode* modes;

    if (monitor->modes)
        return GL_TRUE;

    modes = _glfwPlatformGetVideoModes(monitor, &modeCount);
    if (!modes)
        return GL_FALSE;

    qsort(modes, modeCount, sizeof(GLFWvidmode), compareVideoModes);

    free(monitor->modes);
    monitor->modes = modes;
    monitor->modeCount = modeCount;

    return GL_TRUE;
}