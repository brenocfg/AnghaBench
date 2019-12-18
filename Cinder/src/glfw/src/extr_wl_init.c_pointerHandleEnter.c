#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wl_fixed_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct wl_surface {int dummy; } ;
struct wl_pointer {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  currentCursor; } ;
struct TYPE_10__ {TYPE_2__ wl; } ;
typedef  TYPE_3__ _GLFWwindow ;
struct TYPE_8__ {TYPE_3__* pointerFocus; int /*<<< orphan*/  pointerSerial; } ;
struct TYPE_11__ {TYPE_1__ wl; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_TRUE ; 
 TYPE_7__ _glfw ; 
 int /*<<< orphan*/  _glfwInputCursorEnter (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _glfwPlatformSetCursor (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* wl_surface_get_user_data (struct wl_surface*) ; 

__attribute__((used)) static void pointerHandleEnter(void* data,
                               struct wl_pointer* pointer,
                               uint32_t serial,
                               struct wl_surface* surface,
                               wl_fixed_t sx,
                               wl_fixed_t sy)
{
    _GLFWwindow* window = wl_surface_get_user_data(surface);

    _glfw.wl.pointerSerial = serial;
    _glfw.wl.pointerFocus = window;

    _glfwPlatformSetCursor(window, window->wl.currentCursor);
    _glfwInputCursorEnter(window, GLFW_TRUE);
}