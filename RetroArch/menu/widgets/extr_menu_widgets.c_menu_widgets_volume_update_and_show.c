#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {float audio_volume; } ;
struct TYPE_7__ {TYPE_1__ floats; } ;
typedef  TYPE_2__ settings_t ;
struct TYPE_8__ {int /*<<< orphan*/ * userdata; int /*<<< orphan*/  duration; int /*<<< orphan*/  cb; } ;
typedef  TYPE_3__ menu_timer_ctx_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_ACTION_MUTE_ENABLE ; 
 int /*<<< orphan*/  DEFAULT_BACKDROP ; 
 int /*<<< orphan*/  VOLUME_DURATION ; 
 int* audio_get_bool_ptr (int /*<<< orphan*/ ) ; 
 TYPE_2__* config_get_ptr () ; 
 int /*<<< orphan*/  menu_animation_kill_by_tag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  menu_timer_start (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  menu_widgets_volume_timer_end ; 
 int /*<<< orphan*/  pow (int,float) ; 
 int /*<<< orphan*/  volume_alpha ; 
 float volume_db ; 
 int volume_mute ; 
 int /*<<< orphan*/  volume_percent ; 
 int /*<<< orphan*/  volume_tag ; 
 float volume_text_alpha ; 
 int /*<<< orphan*/  volume_timer ; 

void menu_widgets_volume_update_and_show(void)
{
   settings_t *settings = config_get_ptr();
   bool mute            = *(audio_get_bool_ptr(AUDIO_ACTION_MUTE_ENABLE));
   float new_volume     = settings->floats.audio_volume;
   menu_timer_ctx_entry_t entry;

   menu_animation_kill_by_tag(&volume_tag);

   volume_db         = new_volume;
   volume_percent    = pow(10, new_volume/20);
   volume_alpha      = DEFAULT_BACKDROP;
   volume_text_alpha = 1.0f;
   volume_mute       = mute;

   entry.cb          = menu_widgets_volume_timer_end;
   entry.duration    = VOLUME_DURATION;
   entry.userdata    = NULL;

   menu_timer_start(&volume_timer, &entry);
}