#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int modesCount; TYPE_1__* modes; } ;
struct TYPE_7__ {TYPE_2__ wl; } ;
typedef  TYPE_3__ _GLFWmonitor ;
struct TYPE_5__ {int /*<<< orphan*/  base; } ;
typedef  int /*<<< orphan*/  GLFWvidmode ;

/* Variables and functions */
 int /*<<< orphan*/ * calloc (int,int) ; 

GLFWvidmode* _glfwPlatformGetVideoModes(_GLFWmonitor* monitor, int* found)
{
    GLFWvidmode *modes;
    int i, modesCount = monitor->wl.modesCount;

    modes = calloc(modesCount, sizeof(GLFWvidmode));

    for (i = 0;  i < modesCount;  i++)
        modes[i] = monitor->wl.modes[i].base;

    *found = modesCount;
    return modes;
}