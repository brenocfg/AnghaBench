#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int kiosk_mode_enable; } ;
struct TYPE_5__ {int /*<<< orphan*/  kiosk_mode_password; } ;
struct TYPE_7__ {TYPE_2__ bools; TYPE_1__ paths; } ;
typedef  TYPE_3__ settings_t ;

/* Variables and functions */
 int /*<<< orphan*/  MESSAGE_QUEUE_CATEGORY_INFO ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_ICON_DEFAULT ; 
 int /*<<< orphan*/  MSG_INPUT_KIOSK_MODE_PASSWORD_NOK ; 
 int /*<<< orphan*/  MSG_INPUT_KIOSK_MODE_PASSWORD_OK ; 
 TYPE_3__* config_get_ptr () ; 
 int /*<<< orphan*/  menu_input_dialog_end () ; 
 char* menu_input_dialog_get_buffer () ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  runloop_msg_queue_push (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ string_is_equal (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void menu_input_st_string_cb_disable_kiosk_mode(void *userdata,
      const char *str)
{
   if (str && *str)
   {
      const char *label = menu_input_dialog_get_buffer();
      settings_t *settings = config_get_ptr();

      if (string_is_equal(label, settings->paths.kiosk_mode_password))
      {
         settings->bools.kiosk_mode_enable = false;

         runloop_msg_queue_push(
            msg_hash_to_str(MSG_INPUT_KIOSK_MODE_PASSWORD_OK),
            1, 100, true,
            NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);
      }
      else
      {
         runloop_msg_queue_push(
            msg_hash_to_str(MSG_INPUT_KIOSK_MODE_PASSWORD_NOK),
            1, 100, true,
            NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);
      }
   }

   menu_input_dialog_end();
}