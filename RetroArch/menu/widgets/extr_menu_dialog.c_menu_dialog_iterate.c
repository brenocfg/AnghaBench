#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct retro_keybind {int dummy; } ;
struct TYPE_12__ {int bundle_finished; } ;
struct TYPE_13__ {TYPE_1__ bools; } ;
typedef  TYPE_2__ settings_t ;
typedef  int /*<<< orphan*/  s2 ;
struct TYPE_14__ {char* s; size_t len; int /*<<< orphan*/  idx; } ;
typedef  TYPE_3__ rcheevos_ctx_desc_t ;
struct TYPE_15__ {int /*<<< orphan*/  timer_end; } ;
typedef  TYPE_4__ rarch_timer_t ;
typedef  int /*<<< orphan*/  desc ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (unsigned int const*) ; 
#define  MENU_DIALOG_ERROR 143 
#define  MENU_DIALOG_HELP_AUDIO_VIDEO_TROUBLESHOOTING 142 
#define  MENU_DIALOG_HELP_CHANGE_VIRTUAL_GAMEPAD 141 
#define  MENU_DIALOG_HELP_CHEEVOS_DESCRIPTION 140 
#define  MENU_DIALOG_HELP_CONTROLS 139 
#define  MENU_DIALOG_HELP_EXTRACT 138 
#define  MENU_DIALOG_HELP_LOADING_CONTENT 137 
#define  MENU_DIALOG_HELP_SCANNING_CONTENT 136 
#define  MENU_DIALOG_HELP_SEND_DEBUG_INFO 135 
#define  MENU_DIALOG_HELP_WHAT_IS_A_CORE 134 
#define  MENU_DIALOG_INFORMATION 133 
#define  MENU_DIALOG_NONE 132 
#define  MENU_DIALOG_QUESTION 131 
#define  MENU_DIALOG_QUIT_CONFIRM 130 
#define  MENU_DIALOG_WARNING 129 
#define  MENU_DIALOG_WELCOME 128 
 int /*<<< orphan*/  MENU_ENUM_LABEL_LOAD_CONTENT_LIST ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_BASIC_MENU_CONTROLS_BACK ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_BASIC_MENU_CONTROLS_CONFIRM ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_BASIC_MENU_CONTROLS_INFO ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_BASIC_MENU_CONTROLS_QUIT ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_BASIC_MENU_CONTROLS_SCROLL_DOWN ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_BASIC_MENU_CONTROLS_SCROLL_UP ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_BASIC_MENU_CONTROLS_START ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_BASIC_MENU_CONTROLS_TOGGLE_KEYBOARD ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_BASIC_MENU_CONTROLS_TOGGLE_MENU ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_EXTRACTING_PLEASE_WAIT ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_HELP_AUDIO_VIDEO_TROUBLESHOOTING_DESC ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_HELP_CHANGE_VIRTUAL_GAMEPAD_DESC ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_HELP_SCANNING_CONTENT_DESC ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_HELP_SEND_DEBUG_INFO_DESC ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_MENU_ENUM_CONTROLS_PROLOG ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_WHAT_IS_A_CORE_DESC ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_WELCOME_TO_RETROARCH ; 
 int PATH_MAX_LENGTH ; 
 unsigned int const RARCH_MENU_TOGGLE ; 
 unsigned int const RARCH_QUIT_KEY ; 
 unsigned int const RETRO_DEVICE_ID_JOYPAD_A ; 
 unsigned int const RETRO_DEVICE_ID_JOYPAD_B ; 
 unsigned int const RETRO_DEVICE_ID_JOYPAD_DOWN ; 
 unsigned int const RETRO_DEVICE_ID_JOYPAD_SELECT ; 
 unsigned int const RETRO_DEVICE_ID_JOYPAD_START ; 
 unsigned int const RETRO_DEVICE_ID_JOYPAD_UP ; 
 unsigned int const RETRO_DEVICE_ID_JOYPAD_X ; 
 unsigned int const RETRO_DEVICE_ID_JOYPAD_Y ; 
 TYPE_2__* config_get_ptr () ; 
 struct retro_keybind** input_config_binds ; 
 scalar_t__ input_config_get_bind_auto (int /*<<< orphan*/ ,unsigned int const) ; 
 int /*<<< orphan*/  input_config_get_bind_string (char*,struct retro_keybind const*,struct retro_keybind const*,int) ; 
 int /*<<< orphan*/  menu_dialog_current_id ; 
 int /*<<< orphan*/  menu_dialog_current_msg ; 
 int menu_dialog_current_type ; 
 int /*<<< orphan*/  menu_hash_get_help_enum (int /*<<< orphan*/ ,char*,size_t) ; 
 char* msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rarch_timer_begin (TYPE_4__*,int) ; 
 int /*<<< orphan*/  rarch_timer_end (TYPE_4__*) ; 
 int /*<<< orphan*/  rarch_timer_has_expired (TYPE_4__*) ; 
 int /*<<< orphan*/  rarch_timer_is_running (TYPE_4__*) ; 
 int /*<<< orphan*/  rarch_timer_tick (TYPE_4__*) ; 
 int /*<<< orphan*/  rcheevos_get_description (TYPE_3__*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*) ; 

int menu_dialog_iterate(char *s, size_t len, const char *label)
{
#ifdef HAVE_CHEEVOS
   rcheevos_ctx_desc_t desc_info;
#endif
   bool do_exit              = false;

   switch (menu_dialog_current_type)
   {
      case MENU_DIALOG_WELCOME:
         {
            static rarch_timer_t timer;

            if (!rarch_timer_is_running(&timer))
               rarch_timer_begin(&timer, 3);

            rarch_timer_tick(&timer);

            menu_hash_get_help_enum(
                  MENU_ENUM_LABEL_WELCOME_TO_RETROARCH,
                  s, len);

            if (!timer.timer_end && rarch_timer_has_expired(&timer))
            {
               rarch_timer_end(&timer);
               do_exit     = true;
            }
         }
         break;
      case MENU_DIALOG_HELP_CONTROLS:
         {
            unsigned i;
            char s2[PATH_MAX_LENGTH];
            const unsigned binds[] = {
               RETRO_DEVICE_ID_JOYPAD_UP,
               RETRO_DEVICE_ID_JOYPAD_DOWN,
               RETRO_DEVICE_ID_JOYPAD_A,
               RETRO_DEVICE_ID_JOYPAD_B,
               RETRO_DEVICE_ID_JOYPAD_SELECT,
               RETRO_DEVICE_ID_JOYPAD_START,
               RARCH_MENU_TOGGLE,
               RARCH_QUIT_KEY,
               RETRO_DEVICE_ID_JOYPAD_X,
               RETRO_DEVICE_ID_JOYPAD_Y,
            };
            char desc[ARRAY_SIZE(binds)][64];

            for (i = 0; i < ARRAY_SIZE(binds); i++)
               desc[i][0] = '\0';

            for (i = 0; i < ARRAY_SIZE(binds); i++)
            {
               const struct retro_keybind *keybind = &input_config_binds[0][binds[i]];
               const struct retro_keybind *auto_bind =
                  (const struct retro_keybind*)
                  input_config_get_bind_auto(0, binds[i]);

               input_config_get_bind_string(desc[i],
                     keybind, auto_bind, sizeof(desc[i]));
            }

            s2[0] = '\0';

            menu_hash_get_help_enum(MENU_ENUM_LABEL_VALUE_MENU_ENUM_CONTROLS_PROLOG,
                  s2, sizeof(s2));

            snprintf(s, len,
                  "%s"
                  "[%s]: "
                  "%-20s\n"
                  "[%s]: "
                  "%-20s\n"
                  "[%s]: "
                  "%-20s\n"
                  "[%s]: "
                  "%-20s\n"
                  "[%s]: "
                  "%-20s\n"
                  "[%s]: "
                  "%-20s\n"
                  "[%s]: "
                  "%-20s\n"
                  "[%s]: "
                  "%-20s\n"
                  "[%s]: "
                  "%-20s\n",

                  s2,

                  msg_hash_to_str(
                        MENU_ENUM_LABEL_VALUE_BASIC_MENU_CONTROLS_SCROLL_UP),
                  desc[0],

                  msg_hash_to_str(
                        MENU_ENUM_LABEL_VALUE_BASIC_MENU_CONTROLS_SCROLL_DOWN),
                  desc[1],

                  msg_hash_to_str(
                        MENU_ENUM_LABEL_VALUE_BASIC_MENU_CONTROLS_CONFIRM),
                  desc[2],

                  msg_hash_to_str(
                        MENU_ENUM_LABEL_VALUE_BASIC_MENU_CONTROLS_BACK),
                  desc[3],

                  msg_hash_to_str(
                        MENU_ENUM_LABEL_VALUE_BASIC_MENU_CONTROLS_INFO),
                  desc[4],

                  msg_hash_to_str(
                        MENU_ENUM_LABEL_VALUE_BASIC_MENU_CONTROLS_START),
                  desc[5],

                  msg_hash_to_str(
                        MENU_ENUM_LABEL_VALUE_BASIC_MENU_CONTROLS_TOGGLE_MENU),
                  desc[6],

                  msg_hash_to_str(
                        MENU_ENUM_LABEL_VALUE_BASIC_MENU_CONTROLS_QUIT),
                  desc[7],

                  msg_hash_to_str(
                        MENU_ENUM_LABEL_VALUE_BASIC_MENU_CONTROLS_TOGGLE_KEYBOARD),
                  desc[8]

                  );
         }
         break;

#ifdef HAVE_CHEEVOS
      case MENU_DIALOG_HELP_CHEEVOS_DESCRIPTION:
         desc_info.idx = menu_dialog_current_id;
         desc_info.s   = s;
         desc_info.len = len;
         rcheevos_get_description((rcheevos_ctx_desc_t*) &desc_info);
         break;
#endif

      case MENU_DIALOG_HELP_WHAT_IS_A_CORE:
         menu_hash_get_help_enum(MENU_ENUM_LABEL_VALUE_WHAT_IS_A_CORE_DESC,
               s, len);
         break;
      case MENU_DIALOG_HELP_LOADING_CONTENT:
         menu_hash_get_help_enum(MENU_ENUM_LABEL_LOAD_CONTENT_LIST,
               s, len);
         break;
      case MENU_DIALOG_HELP_CHANGE_VIRTUAL_GAMEPAD:
         menu_hash_get_help_enum(
               MENU_ENUM_LABEL_VALUE_HELP_CHANGE_VIRTUAL_GAMEPAD_DESC,
               s, len);
         break;
      case MENU_DIALOG_HELP_AUDIO_VIDEO_TROUBLESHOOTING:
         menu_hash_get_help_enum(
               MENU_ENUM_LABEL_VALUE_HELP_AUDIO_VIDEO_TROUBLESHOOTING_DESC,
               s, len);
         break;
      case MENU_DIALOG_HELP_SEND_DEBUG_INFO:
         menu_hash_get_help_enum(
               MENU_ENUM_LABEL_VALUE_HELP_SEND_DEBUG_INFO_DESC,
               s, len);
         break;
      case MENU_DIALOG_HELP_SCANNING_CONTENT:
         menu_hash_get_help_enum(MENU_ENUM_LABEL_VALUE_HELP_SCANNING_CONTENT_DESC,
               s, len);
         break;
      case MENU_DIALOG_HELP_EXTRACT:
         {
            settings_t *settings      = config_get_ptr();
            menu_hash_get_help_enum(MENU_ENUM_LABEL_VALUE_EXTRACTING_PLEASE_WAIT,
                  s, len);

            if (settings->bools.bundle_finished)
            {
               settings->bools.bundle_finished = false;
               do_exit                         = true;
            }
         }
         break;
      case MENU_DIALOG_QUIT_CONFIRM:
      case MENU_DIALOG_INFORMATION:
      case MENU_DIALOG_QUESTION:
      case MENU_DIALOG_WARNING:
      case MENU_DIALOG_ERROR:
         menu_hash_get_help_enum(menu_dialog_current_msg,
               s, len);
         break;
      case MENU_DIALOG_NONE:
      default:
         break;
   }

   if (do_exit)
   {
      menu_dialog_current_type = MENU_DIALOG_NONE;
      return 1;
   }

   return 0;
}