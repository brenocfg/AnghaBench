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
typedef  int /*<<< orphan*/  qnx_input_t ;
typedef  int /*<<< orphan*/  navigator_window_state_t ;
typedef  int /*<<< orphan*/  bps_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_EVENT_MENU_TOGGLE ; 
#define  NAVIGATOR_EXIT 137 
#define  NAVIGATOR_SWIPE_DOWN 136 
#define  NAVIGATOR_SYSKEY_BACK 135 
#define  NAVIGATOR_SYSKEY_END 134 
#define  NAVIGATOR_SYSKEY_PRESS 133 
#define  NAVIGATOR_SYSKEY_SEND 132 
#define  NAVIGATOR_WINDOW_FULLSCREEN 131 
#define  NAVIGATOR_WINDOW_INVISIBLE 130 
#define  NAVIGATOR_WINDOW_STATE 129 
#define  NAVIGATOR_WINDOW_THUMBNAIL 128 
 int /*<<< orphan*/  RARCH_CTL_SET_SHUTDOWN ; 
 int /*<<< orphan*/  RETROK_BACKSPACE ; 
 int /*<<< orphan*/  RETRO_DEVICE_KEYBOARD ; 
 int bps_event_get_code (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bps_get_event (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  command_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_keyboard_event (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  navigator_event_get_syskey_key (int /*<<< orphan*/ *) ; 
 int navigator_event_get_window_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rarch_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qnx_handle_navigator_event(
      qnx_input_t *qnx, bps_event_t *event)
{
   navigator_window_state_t state;
   bps_event_t *event_pause = NULL;

   switch (bps_event_get_code(event))
   {
      case NAVIGATOR_SYSKEY_PRESS:
         switch(navigator_event_get_syskey_key(event))
         {
            case NAVIGATOR_SYSKEY_BACK:
               input_keyboard_event(true, RETROK_BACKSPACE, 0, 0, RETRO_DEVICE_KEYBOARD);
               input_keyboard_event(false, RETROK_BACKSPACE, 0, 0, RETRO_DEVICE_KEYBOARD);
               break;
            case NAVIGATOR_SYSKEY_SEND:
            case NAVIGATOR_SYSKEY_END:
               break;
            default:
               break;
         }
         break;
      case NAVIGATOR_SWIPE_DOWN:
         command_event(CMD_EVENT_MENU_TOGGLE, NULL);
         break;
      case NAVIGATOR_WINDOW_STATE:
         switch(navigator_event_get_window_state(event))
         {
            case NAVIGATOR_WINDOW_THUMBNAIL:
            case NAVIGATOR_WINDOW_INVISIBLE:
               while(true)
               {
                  unsigned event_code;

                  /* Block until we get a resume or exit event. */
                  bps_get_event(&event_pause, -1);
                  event_code = bps_event_get_code(event_pause);

                  if(event_code == NAVIGATOR_WINDOW_STATE)
                  {
                     if(navigator_event_get_window_state(event_pause) == NAVIGATOR_WINDOW_FULLSCREEN)
                        break;
                  }
                  else if(event_code == NAVIGATOR_EXIT)
                     goto shutdown;
               }
               break;
            case NAVIGATOR_WINDOW_FULLSCREEN:
               break;
         }
         break;
     case NAVIGATOR_EXIT:
        goto shutdown;
      default:
         break;
   }

   return;

   togglemenu:
       command_event(CMD_EVENT_MENU_TOGGLE, NULL);
       return;
   shutdown:
       rarch_ctl(RARCH_CTL_SET_SHUTDOWN, NULL);
       return;
}