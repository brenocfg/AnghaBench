#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  status; } ;
typedef  TYPE_1__ discord_userdata_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_EVENT_DISCORD_UPDATE ; 
 int /*<<< orphan*/  DISCORD_PRESENCE_GAME_PAUSED ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_CATEGORY_INFO ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_ICON_DEFAULT ; 
 int /*<<< orphan*/  MSG_PAUSED ; 
 int /*<<< orphan*/  MSG_UNPAUSED ; 
 int /*<<< orphan*/  RARCH_LOG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  command_event (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int menu_widgets_ai_service_overlay_get_state () ; 
 int /*<<< orphan*/  menu_widgets_ai_service_overlay_unload () ; 
 scalar_t__ menu_widgets_inited ; 
 int menu_widgets_paused ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int runloop_idle ; 
 int /*<<< orphan*/  runloop_msg_queue_push (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int runloop_paused ; 
 int /*<<< orphan*/  video_driver_cached_frame () ; 

__attribute__((used)) static void retroarch_pause_checks(void)
{
#ifdef HAVE_DISCORD
   discord_userdata_t userdata;
#endif
   bool is_paused            = runloop_paused;
   bool is_idle              = runloop_idle;

   if (is_paused)
   {
      RARCH_LOG("%s\n", msg_hash_to_str(MSG_PAUSED));

#if defined(HAVE_MENU) && defined(HAVE_MENU_WIDGETS)
      if (menu_widgets_inited)
         menu_widgets_paused = is_paused;
      else
#endif
         runloop_msg_queue_push(msg_hash_to_str(MSG_PAUSED), 1,
               1, true,
               NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);


      if (!is_idle)
         video_driver_cached_frame();

#ifdef HAVE_DISCORD
      userdata.status = DISCORD_PRESENCE_GAME_PAUSED;
      command_event(CMD_EVENT_DISCORD_UPDATE, &userdata);
#endif
   }
   else
   {
#if defined(HAVE_MENU) && defined(HAVE_MENU_WIDGETS)
      if (menu_widgets_inited)
         menu_widgets_paused = is_paused;
#endif
      RARCH_LOG("%s\n", msg_hash_to_str(MSG_UNPAUSED));

   }

#ifdef HAVE_MENU_WIDGETS
   if (menu_widgets_ai_service_overlay_get_state() == 1)
      menu_widgets_ai_service_overlay_unload();
#endif
}