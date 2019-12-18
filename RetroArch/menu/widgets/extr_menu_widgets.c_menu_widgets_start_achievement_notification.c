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
struct TYPE_6__ {int video_font_size; } ;
struct TYPE_7__ {TYPE_1__ floats; } ;
typedef  TYPE_2__ settings_t ;
struct TYPE_8__ {float* subject; float target_value; int /*<<< orphan*/ * userdata; int /*<<< orphan*/  tag; int /*<<< orphan*/  easing_enum; int /*<<< orphan*/  duration; int /*<<< orphan*/  cb; } ;
typedef  TYPE_3__ menu_animation_ctx_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  EASING_OUT_QUAD ; 
 int MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSG_ACHIEVEMENT_UNLOCKED ; 
 int /*<<< orphan*/  MSG_QUEUE_ANIMATION_DURATION ; 
 int cheevo_height ; 
 int /*<<< orphan*/  cheevo_title ; 
 float cheevo_unfold ; 
 int cheevo_width ; 
 float cheevo_y ; 
 TYPE_2__* config_get_ptr () ; 
 int /*<<< orphan*/  font_driver_get_message_width (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  font_regular ; 
 int /*<<< orphan*/  menu_animation_push (TYPE_3__*) ; 
 int /*<<< orphan*/  menu_widgets_achievement_unfold ; 
 int /*<<< orphan*/  menu_widgets_generic_tag ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int simple_widget_padding ; 

__attribute__((used)) static void menu_widgets_start_achievement_notification()
{
   settings_t *settings = config_get_ptr();
   menu_animation_ctx_entry_t entry;
   cheevo_height  = settings->floats.video_font_size * 4;
   cheevo_width   = MAX(
         font_driver_get_message_width(font_regular, msg_hash_to_str(MSG_ACHIEVEMENT_UNLOCKED), 0, 1),
         font_driver_get_message_width(font_regular, cheevo_title, 0, 1)
   );
   cheevo_width += simple_widget_padding * 2;
   cheevo_y       = (float)(-(int)cheevo_height);
   cheevo_unfold  = 0.0f;

   /* Slide down animation */
   entry.cb             = menu_widgets_achievement_unfold;
   entry.duration       = MSG_QUEUE_ANIMATION_DURATION;
   entry.easing_enum    = EASING_OUT_QUAD;
   entry.subject        = &cheevo_y;
   entry.tag            = menu_widgets_generic_tag;
   entry.target_value   = 0.0f;
   entry.userdata       = NULL;

   menu_animation_push(&entry);
}