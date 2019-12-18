#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ video_fullscreen; } ;
struct TYPE_8__ {TYPE_1__ bools; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* poll ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  (* set_nonblock_state ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_EVENT_GAME_FOCUS_TOGGLE ; 
 int /*<<< orphan*/  command_event (int /*<<< orphan*/ ,void*) ; 
 TYPE_4__* configuration_settings ; 
 TYPE_3__* current_input ; 
 int /*<<< orphan*/  current_input_data ; 
 TYPE_2__* current_video ; 
 int /*<<< orphan*/  menu_display_set_framebuffer_dirty_flag () ; 
 scalar_t__ menu_driver_alive ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_driver_data ; 
 int /*<<< orphan*/  video_driver_hide_mouse () ; 
 int /*<<< orphan*/  video_driver_reinit (int const) ; 

__attribute__((used)) static void command_event_reinit(const int flags)
{
   video_driver_reinit(flags);
   /* Poll input to avoid possibly stale data to corrupt things. */
   if (current_input && current_input->poll)
      current_input->poll(current_input_data);
   command_event(CMD_EVENT_GAME_FOCUS_TOGGLE, (void*)(intptr_t)-1);

#ifdef HAVE_MENU
   menu_display_set_framebuffer_dirty_flag();
   if (configuration_settings->bools.video_fullscreen)
      video_driver_hide_mouse();
   if (menu_driver_alive && current_video->set_nonblock_state)
      current_video->set_nonblock_state(video_driver_data, false);
#endif
}