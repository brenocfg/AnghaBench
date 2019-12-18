#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct android_app {int /*<<< orphan*/  inputQueue; } ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  android_input_t ;
typedef  int /*<<< orphan*/  AInputEvent ;

/* Variables and functions */
#define  AINPUT_EVENT_TYPE_KEY 129 
#define  AINPUT_EVENT_TYPE_MOTION 128 
 int AInputEvent_getSource (int /*<<< orphan*/ *) ; 
 int AInputEvent_getType (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AInputQueue_finishEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ AInputQueue_getEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ AInputQueue_hasEvents (int /*<<< orphan*/ ) ; 
 int AInputQueue_preDispatchEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int AKeyEvent_getKeyCode (int /*<<< orphan*/ *) ; 
 int ANDROID_KEYBOARD_PORT ; 
 int android_input_get_id (int /*<<< orphan*/ *) ; 
 int android_input_get_id_port (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  android_input_poll_event_type_key (struct android_app*,int /*<<< orphan*/ *,int,int,int,int,int*) ; 
 int /*<<< orphan*/  android_input_poll_event_type_keyboard (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  android_input_poll_event_type_motion (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  engine_handle_dpad (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ g_android ; 
 int /*<<< orphan*/  handle_hotplug (int /*<<< orphan*/ *,struct android_app*,int*,int,int) ; 
 scalar_t__ is_keyboard_id (int) ; 

__attribute__((used)) static void android_input_poll_input(android_input_t *android)
{
   AInputEvent              *event = NULL;
   struct android_app *android_app = (struct android_app*)g_android;

   /* Read all pending events. */
   while (AInputQueue_hasEvents(android_app->inputQueue))
   {
      while (AInputQueue_getEvent(android_app->inputQueue, &event) >= 0)
      {
         int32_t   handled = 1;
         int predispatched = AInputQueue_preDispatchEvent(android_app->inputQueue, event);
         int        source = AInputEvent_getSource(event);
         int    type_event = AInputEvent_getType(event);
         int            id = android_input_get_id(event);
         int          port = android_input_get_id_port(android, id, source);

         if (port < 0 && !is_keyboard_id(id))
            handle_hotplug(android, android_app,
            &port, id, source);

         switch (type_event)
         {
            case AINPUT_EVENT_TYPE_MOTION:
               if (android_input_poll_event_type_motion(android, event,
                        port, source))
                  engine_handle_dpad(android, event, port, source);
               break;
            case AINPUT_EVENT_TYPE_KEY:
               {
                  int keycode = AKeyEvent_getKeyCode(event);

                  if (is_keyboard_id(id))
                  {
                     if (!predispatched)
                     {
                        android_input_poll_event_type_keyboard(event, keycode, &handled);
                        android_input_poll_event_type_key(android_app, event, ANDROID_KEYBOARD_PORT, keycode, source, type_event, &handled);
                     }
                  }
                  else
                     android_input_poll_event_type_key(android_app,
                        event, port, keycode, source, type_event, &handled);
               }
               break;
         }

         if (!predispatched)
            AInputQueue_finishEvent(android_app->inputQueue, event,
                  handled);
      }
   }
}