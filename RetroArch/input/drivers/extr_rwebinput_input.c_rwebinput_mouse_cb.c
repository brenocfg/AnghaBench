#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_5__ {int buttons; int /*<<< orphan*/  delta_y; int /*<<< orphan*/  delta_x; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_4__ {int button; scalar_t__ movementY; scalar_t__ movementX; int /*<<< orphan*/  canvasY; int /*<<< orphan*/  canvasX; } ;
typedef  TYPE_1__ EmscriptenMouseEvent ;
typedef  int /*<<< orphan*/  EM_BOOL ;

/* Variables and functions */
 int EMSCRIPTEN_EVENT_MOUSEDOWN ; 
 int EMSCRIPTEN_EVENT_MOUSEUP ; 
 int /*<<< orphan*/  EM_TRUE ; 
 TYPE_3__* g_rwebinput_mouse ; 

__attribute__((used)) static EM_BOOL rwebinput_mouse_cb(int event_type,
   const EmscriptenMouseEvent *mouse_event, void *user_data)
{
   (void)user_data;

   uint8_t mask = 1 << mouse_event->button;

   g_rwebinput_mouse->x = mouse_event->canvasX;
   g_rwebinput_mouse->y = mouse_event->canvasY;
   g_rwebinput_mouse->delta_x += mouse_event->movementX;
   g_rwebinput_mouse->delta_y += mouse_event->movementY;

   if (event_type ==  EMSCRIPTEN_EVENT_MOUSEDOWN)
   {
      g_rwebinput_mouse->buttons |= mask;
   }
   else if (event_type == EMSCRIPTEN_EVENT_MOUSEUP)
   {
      g_rwebinput_mouse->buttons &= ~mask;
   }

   return EM_TRUE;
}