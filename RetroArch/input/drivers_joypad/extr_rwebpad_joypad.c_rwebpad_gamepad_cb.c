#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ident; } ;
struct TYPE_4__ {int /*<<< orphan*/  index; int /*<<< orphan*/  id; int /*<<< orphan*/  mapping; } ;
typedef  TYPE_1__ EmscriptenGamepadEvent ;
typedef  int /*<<< orphan*/  EM_BOOL ;

/* Variables and functions */
 int EMSCRIPTEN_EVENT_GAMEPADCONNECTED ; 
 int EMSCRIPTEN_EVENT_GAMEPADDISCONNECTED ; 
 int /*<<< orphan*/  EM_TRUE ; 
 int /*<<< orphan*/  input_autoconfigure_connect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  input_autoconfigure_disconnect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ rwebpad_joypad ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static EM_BOOL rwebpad_gamepad_cb(int event_type,
   const EmscriptenGamepadEvent *gamepad_event, void *user_data)
{
   unsigned vid = 0;
   unsigned pid = 0;

   (void)event_type;
   (void)gamepad_event;
   (void)user_data;

   if (strncmp(gamepad_event->mapping, "standard",
       sizeof(gamepad_event->mapping)) == 0)
   {
      /* give a dummy vid/pid for automapping */
      vid = 1;
      pid = 1;
   }

   if (event_type == EMSCRIPTEN_EVENT_GAMEPADCONNECTED)
      input_autoconfigure_connect(
               gamepad_event->id,    /* name */
               NULL,                 /* display name */
               rwebpad_joypad.ident, /* driver */
               gamepad_event->index, /* idx */
               vid,                  /* vid */
               pid);                 /* pid */
   else if (event_type == EMSCRIPTEN_EVENT_GAMEPADDISCONNECTED)
      input_autoconfigure_disconnect(gamepad_event->index,
         rwebpad_joypad.ident);

   return EM_TRUE;
}