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
struct TYPE_2__ {int /*<<< orphan*/  hwnd; } ;
typedef  TYPE_1__ ui_window_win32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DragAcceptFiles_func (int /*<<< orphan*/ ,int) ; 

void ui_window_win32_set_droppable(void *data, bool droppable)
{
   /* Minimum supported client: Windows XP, minimum supported server: Windows 2000 Server */
   ui_window_win32_t *window = (ui_window_win32_t*)data;
   if (DragAcceptFiles_func != NULL)
      DragAcceptFiles_func(window->hwnd, droppable);
}