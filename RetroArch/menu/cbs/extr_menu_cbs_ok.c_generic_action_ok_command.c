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
struct TYPE_4__ {scalar_t__ audio_enable_menu_ok; scalar_t__ audio_enable_menu; } ;
struct TYPE_5__ {TYPE_1__ bools; } ;
typedef  TYPE_2__ settings_t ;
typedef  enum event_command { ____Placeholder_event_command } event_command ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_MIXER_SYSTEM_SLOT_OK ; 
 int /*<<< orphan*/  audio_driver_mixer_play_menu_sound (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  command_event (int,int /*<<< orphan*/ *) ; 
 TYPE_2__* config_get_ptr () ; 
 int menu_cbs_exit () ; 

int generic_action_ok_command(enum event_command cmd)
{
#ifdef HAVE_AUDIOMIXER
   settings_t *settings = config_get_ptr();

   if (settings->bools.audio_enable_menu && settings->bools.audio_enable_menu_ok)
      audio_driver_mixer_play_menu_sound(AUDIO_MIXER_SYSTEM_SLOT_OK);
#endif

   if (!command_event(cmd, NULL))
      return menu_cbs_exit();
   return 0;
}