#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ output_id; } ;
struct TYPE_6__ {TYPE_1__ mir; } ;
typedef  TYPE_2__ _GLFWmonitor ;
typedef  int GLboolean ;

/* Variables and functions */

GLboolean _glfwPlatformIsSameMonitor(_GLFWmonitor* first, _GLFWmonitor* second)
{
    return first->mir.output_id == second->mir.output_id;
}