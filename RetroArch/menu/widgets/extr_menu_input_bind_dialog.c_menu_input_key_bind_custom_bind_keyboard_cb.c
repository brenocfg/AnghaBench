#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  input_bind_timeout; int /*<<< orphan*/  input_bind_hold; } ;
struct TYPE_8__ {TYPE_1__ uints; } ;
typedef  TYPE_3__ settings_t ;
typedef  enum retro_key { ____Placeholder_retro_key } retro_key ;
struct TYPE_7__ {int key; } ;
struct TYPE_9__ {scalar_t__ begin; scalar_t__ last; int /*<<< orphan*/  timer_timeout; int /*<<< orphan*/  timer_hold; TYPE_2__* output; TYPE_2__ buffer; } ;

/* Variables and functions */
 TYPE_3__* config_get_ptr () ; 
 TYPE_4__ menu_input_binds ; 
 int /*<<< orphan*/  rarch_timer_begin_new_time (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool menu_input_key_bind_custom_bind_keyboard_cb(
      void *data, unsigned code)
{
   settings_t     *settings = config_get_ptr();

   /* store key in bind */
   menu_input_binds.buffer.key = (enum retro_key)code;

   /* write out the bind */
   *(menu_input_binds.output)=menu_input_binds.buffer;

   /* next bind */
   menu_input_binds.begin++;
   menu_input_binds.output++;
   menu_input_binds.buffer=*(menu_input_binds.output);
   rarch_timer_begin_new_time(&menu_input_binds.timer_hold, settings->uints.input_bind_hold);
   rarch_timer_begin_new_time(&menu_input_binds.timer_timeout, settings->uints.input_bind_timeout);

   return (menu_input_binds.begin <= menu_input_binds.last);
}