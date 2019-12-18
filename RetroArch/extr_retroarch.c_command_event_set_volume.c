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
struct TYPE_5__ {float audio_volume; } ;
struct TYPE_6__ {TYPE_1__ floats; } ;
typedef  TYPE_2__ settings_t ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_ACTION_VOLUME_GAIN ; 
 float MAX (float,float) ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_CATEGORY_INFO ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_ICON_DEFAULT ; 
 float MIN (float,float) ; 
 int /*<<< orphan*/  MSG_AUDIO_VOLUME ; 
 int /*<<< orphan*/  RARCH_LOG (char*,char*) ; 
 int /*<<< orphan*/  audio_set_float (int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  configuration_set_float (TYPE_2__*,float,float) ; 
 TYPE_2__* configuration_settings ; 
 scalar_t__ menu_widgets_inited ; 
 int /*<<< orphan*/  menu_widgets_volume_update_and_show () ; 
 char* msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  runloop_msg_queue_push (char*,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,float) ; 

__attribute__((used)) static void command_event_set_volume(float gain)
{
   char msg[128];
   settings_t *settings      = configuration_settings;
   float new_volume          = settings->floats.audio_volume + gain;

   new_volume                = MAX(new_volume, -80.0f);
   new_volume                = MIN(new_volume, 12.0f);

   configuration_set_float(settings, settings->floats.audio_volume, new_volume);

   snprintf(msg, sizeof(msg), "%s: %.1f dB",
         msg_hash_to_str(MSG_AUDIO_VOLUME),
         new_volume);

#if defined(HAVE_MENU) && defined(HAVE_MENU_WIDGETS)
   if (menu_widgets_inited)
      menu_widgets_volume_update_and_show();
   else
#endif
      runloop_msg_queue_push(msg, 1, 180, true, NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);

   RARCH_LOG("%s\n", msg);

   audio_set_float(AUDIO_ACTION_VOLUME_GAIN, new_volume);
}