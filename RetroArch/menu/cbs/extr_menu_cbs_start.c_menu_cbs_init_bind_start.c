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
typedef  int /*<<< orphan*/  menu_file_list_cbs_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIND_ACTION_START (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int MENU_SETTINGS_AUDIO_MIXER_STREAM_ACTIONS_VOLUME_BEGIN ; 
 unsigned int MENU_SETTINGS_AUDIO_MIXER_STREAM_ACTIONS_VOLUME_END ; 
 int /*<<< orphan*/  action_start_audio_mixer_stream_volume ; 
 int /*<<< orphan*/  action_start_lookup_setting ; 
 scalar_t__ menu_cbs_init_bind_start_compare_label (int /*<<< orphan*/ *) ; 
 scalar_t__ menu_cbs_init_bind_start_compare_type (int /*<<< orphan*/ *,unsigned int) ; 

int menu_cbs_init_bind_start(menu_file_list_cbs_t *cbs,
      const char *path, const char *label, unsigned type, size_t idx)
{
   if (!cbs)
      return -1;

#ifdef HAVE_AUDIOMIXER
   if (type >= MENU_SETTINGS_AUDIO_MIXER_STREAM_ACTIONS_VOLUME_BEGIN
         && type <= MENU_SETTINGS_AUDIO_MIXER_STREAM_ACTIONS_VOLUME_END)
   {
      BIND_ACTION_START(cbs, action_start_audio_mixer_stream_volume);
      return 0;
   }
#endif

   BIND_ACTION_START(cbs, action_start_lookup_setting);

   if (menu_cbs_init_bind_start_compare_label(cbs) == 0)
      return 0;

   if (menu_cbs_init_bind_start_compare_type(cbs, type) == 0)
      return 0;

   return -1;
}