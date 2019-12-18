#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  input_bind_timeout; int /*<<< orphan*/  input_bind_hold; int /*<<< orphan*/ * input_joypad_map; } ;
struct TYPE_12__ {TYPE_1__ uints; } ;
typedef  TYPE_2__ settings_t ;
struct TYPE_13__ {unsigned int index_offset; } ;
typedef  TYPE_3__ rarch_setting_t ;
typedef  int /*<<< orphan*/  menu_handle_t ;
struct TYPE_14__ {int /*<<< orphan*/  cb; int /*<<< orphan*/ * userdata; } ;
typedef  TYPE_4__ input_keyboard_ctx_wait_t ;
typedef  enum menu_input_binds_ctl_state { ____Placeholder_menu_input_binds_ctl_state } menu_input_binds_ctl_state ;
struct TYPE_15__ {int /*<<< orphan*/  timer_timeout; int /*<<< orphan*/  timer_hold; } ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_INPUT_KEYBOARD_CTL_START_WAIT_KEYS ; 
 TYPE_2__* config_get_ptr () ; 
 int /*<<< orphan*/  input_keyboard_ctl (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  menu_bind_port ; 
 int /*<<< orphan*/ * menu_driver_get_ptr () ; 
 TYPE_6__ menu_input_binds ; 
 int /*<<< orphan*/  menu_input_key_bind_custom_bind_keyboard_cb ; 
 int /*<<< orphan*/  menu_input_key_bind_poll_bind_get_rested_axes (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_input_key_bind_poll_bind_state (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int menu_input_key_bind_set_mode_common (int,TYPE_3__*) ; 
 int /*<<< orphan*/  rarch_timer_begin_new_time (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool menu_input_key_bind_set_mode(
      enum menu_input_binds_ctl_state state, void *data)
{
   unsigned index_offset;
   input_keyboard_ctx_wait_t keys;
   rarch_setting_t  *setting = (rarch_setting_t*)data;
   settings_t *settings      = config_get_ptr();
   menu_handle_t       *menu = menu_driver_get_ptr();

   if (!setting || !menu)
      return false;
   if (menu_input_key_bind_set_mode_common(state, setting) == -1)
      return false;

   index_offset      = setting->index_offset;
   menu_bind_port    = settings->uints.input_joypad_map[index_offset];

   menu_input_key_bind_poll_bind_get_rested_axes(
         &menu_input_binds, menu_bind_port);
   menu_input_key_bind_poll_bind_state(
         &menu_input_binds, menu_bind_port, false);

   rarch_timer_begin_new_time(&menu_input_binds.timer_hold, settings->uints.input_bind_hold);
   rarch_timer_begin_new_time(&menu_input_binds.timer_timeout, settings->uints.input_bind_timeout);

   keys.userdata = menu;
   keys.cb       = menu_input_key_bind_custom_bind_keyboard_cb;

   input_keyboard_ctl(RARCH_INPUT_KEYBOARD_CTL_START_WAIT_KEYS, &keys);
   return true;
}