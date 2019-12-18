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
struct TYPE_6__ {int /*<<< orphan*/ * input_mouse_index; } ;
struct TYPE_7__ {int modified; TYPE_1__ uints; } ;
typedef  TYPE_2__ settings_t ;
struct TYPE_8__ {size_t index_offset; } ;
typedef  TYPE_3__ rarch_setting_t ;

/* Variables and functions */
 TYPE_2__* config_get_ptr () ; 

__attribute__((used)) static int setting_action_right_mouse_index(rarch_setting_t *setting, bool wraparound)
{
   settings_t *settings     = config_get_ptr();

   if (!setting)
      return -1;

   ++settings->uints.input_mouse_index[setting->index_offset];
   settings->modified = true;

   return 0;
}