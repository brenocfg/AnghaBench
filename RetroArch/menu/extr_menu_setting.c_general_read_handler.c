#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/ * input_joypad_map; } ;
struct TYPE_12__ {float audio_max_timing_skew; float video_refresh_rate; } ;
struct TYPE_11__ {int /*<<< orphan*/  audio_rate_control; } ;
struct TYPE_16__ {TYPE_5__ uints; TYPE_2__ floats; TYPE_1__ bools; } ;
typedef  TYPE_6__ settings_t ;
struct TYPE_13__ {double* fraction; int /*<<< orphan*/ * integer; } ;
struct TYPE_14__ {TYPE_3__ target; } ;
struct TYPE_17__ {int enum_idx; TYPE_4__ value; } ;
typedef  TYPE_7__ rarch_setting_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_ACTION_RATE_CONTROL_DELTA ; 
#define  MENU_ENUM_LABEL_AUDIO_MAX_TIMING_SKEW 135 
#define  MENU_ENUM_LABEL_AUDIO_RATE_CONTROL_DELTA 134 
#define  MENU_ENUM_LABEL_INPUT_PLAYER1_JOYPAD_INDEX 133 
#define  MENU_ENUM_LABEL_INPUT_PLAYER2_JOYPAD_INDEX 132 
#define  MENU_ENUM_LABEL_INPUT_PLAYER3_JOYPAD_INDEX 131 
#define  MENU_ENUM_LABEL_INPUT_PLAYER4_JOYPAD_INDEX 130 
#define  MENU_ENUM_LABEL_INPUT_PLAYER5_JOYPAD_INDEX 129 
#define  MENU_ENUM_LABEL_VIDEO_REFRESH_RATE_AUTO 128 
 int MSG_UNKNOWN ; 
 double* audio_get_float_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audio_set_float (int /*<<< orphan*/ ,float) ; 
 TYPE_6__* config_get_ptr () ; 
 int /*<<< orphan*/  configuration_set_bool (TYPE_6__*,int /*<<< orphan*/ ,int) ; 

void general_read_handler(rarch_setting_t *setting)
{
   settings_t      *settings = config_get_ptr();

   if (!setting || setting->enum_idx == MSG_UNKNOWN)
      return;

   switch (setting->enum_idx)
   {
      case MENU_ENUM_LABEL_AUDIO_RATE_CONTROL_DELTA:
         *setting->value.target.fraction = *(audio_get_float_ptr(AUDIO_ACTION_RATE_CONTROL_DELTA));
         if (*setting->value.target.fraction < 0.0005)
         {
            configuration_set_bool(settings, settings->bools.audio_rate_control, false);
            audio_set_float(AUDIO_ACTION_RATE_CONTROL_DELTA, 0.0f);
         }
         else
         {
            configuration_set_bool(settings, settings->bools.audio_rate_control, true);
            audio_set_float(AUDIO_ACTION_RATE_CONTROL_DELTA, *setting->value.target.fraction);
         }
         break;
      case MENU_ENUM_LABEL_AUDIO_MAX_TIMING_SKEW:
         *setting->value.target.fraction = settings->floats.audio_max_timing_skew;
         break;
      case MENU_ENUM_LABEL_VIDEO_REFRESH_RATE_AUTO:
         *setting->value.target.fraction = settings->floats.video_refresh_rate;
         break;
      case MENU_ENUM_LABEL_INPUT_PLAYER1_JOYPAD_INDEX:
         *setting->value.target.integer = settings->uints.input_joypad_map[0];
         break;
      case MENU_ENUM_LABEL_INPUT_PLAYER2_JOYPAD_INDEX:
         *setting->value.target.integer = settings->uints.input_joypad_map[1];
         break;
      case MENU_ENUM_LABEL_INPUT_PLAYER3_JOYPAD_INDEX:
         *setting->value.target.integer = settings->uints.input_joypad_map[2];
         break;
      case MENU_ENUM_LABEL_INPUT_PLAYER4_JOYPAD_INDEX:
         *setting->value.target.integer = settings->uints.input_joypad_map[3];
         break;
      case MENU_ENUM_LABEL_INPUT_PLAYER5_JOYPAD_INDEX:
         *setting->value.target.integer = settings->uints.input_joypad_map[4];
         break;
      default:
         break;
   }
}