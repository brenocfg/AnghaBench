#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int cursorPosX; int cursorPosY; } ;
typedef  TYPE_1__ _GLFWwindow ;
typedef  int /*<<< orphan*/  MirPointerEvent ;

/* Variables and functions */
 int /*<<< orphan*/  _glfwInputCursorMotion (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  _glfwInputScroll (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  mir_pointer_axis_hscroll ; 
 int /*<<< orphan*/  mir_pointer_axis_vscroll ; 
 int /*<<< orphan*/  mir_pointer_axis_x ; 
 int /*<<< orphan*/  mir_pointer_axis_y ; 
 int mir_pointer_event_axis_value (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handlePointerMotion(_GLFWwindow* window,
                                const MirPointerEvent* pointer_event)
{
    int current_x = window->cursorPosX;
    int current_y = window->cursorPosY;
    int x  = mir_pointer_event_axis_value(pointer_event, mir_pointer_axis_x);
    int y  = mir_pointer_event_axis_value(pointer_event, mir_pointer_axis_y);
    int dx = mir_pointer_event_axis_value(pointer_event, mir_pointer_axis_hscroll);
    int dy = mir_pointer_event_axis_value(pointer_event, mir_pointer_axis_vscroll);

    if (current_x != x || current_y != y)
      _glfwInputCursorMotion(window, x, y);
    if (dx != 0 || dy != 0)
      _glfwInputScroll(window, dx, dy);
}