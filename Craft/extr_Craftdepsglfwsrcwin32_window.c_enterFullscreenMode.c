#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  handle; } ;
struct TYPE_7__ {TYPE_1__ win32; int /*<<< orphan*/  monitor; int /*<<< orphan*/  videoMode; } ;
typedef  TYPE_2__ _GLFWwindow ;
struct TYPE_8__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  int /*<<< orphan*/  GLboolean ;
typedef  TYPE_3__ GLFWvidmode ;

/* Variables and functions */
 int /*<<< orphan*/  HWND_TOPMOST ; 
 int /*<<< orphan*/  SWP_NOCOPYBITS ; 
 int /*<<< orphan*/  SetWindowPos (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _glfwPlatformGetMonitorPos (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  _glfwPlatformGetVideoMode (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  _glfwSetVideoMode (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static GLboolean enterFullscreenMode(_GLFWwindow* window)
{
    GLFWvidmode mode;
    GLboolean status;
    int xpos, ypos;

    status = _glfwSetVideoMode(window->monitor, &window->videoMode);

    _glfwPlatformGetVideoMode(window->monitor, &mode);
    _glfwPlatformGetMonitorPos(window->monitor, &xpos, &ypos);

    SetWindowPos(window->win32.handle, HWND_TOPMOST,
                 xpos, ypos, mode.width, mode.height, SWP_NOCOPYBITS);

    return status;
}