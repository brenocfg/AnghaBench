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
struct TYPE_5__ {scalar_t__ handle; } ;
struct TYPE_6__ {TYPE_1__ win32; } ;
typedef  TYPE_2__ _GLFWwindow ;
typedef  int /*<<< orphan*/  POINT ;

/* Variables and functions */
 scalar_t__ GetCursorPos (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetCursor (int /*<<< orphan*/ *) ; 
 scalar_t__ WindowFromPoint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  updateClipRect (TYPE_2__*) ; 

__attribute__((used)) static void disableCursor(_GLFWwindow* window)
{
    POINT pos;

    updateClipRect(window);

    if (GetCursorPos(&pos))
    {
        if (WindowFromPoint(pos) == window->win32.handle)
            SetCursor(NULL);
    }
}