#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int port; int /*<<< orphan*/  device; } ;
typedef  TYPE_1__ retro_ctx_controller_info_t ;
struct TYPE_7__ {unsigned int index_offset; } ;
typedef  TYPE_2__ rarch_setting_t ;

/* Variables and functions */
 int /*<<< orphan*/  RETRO_DEVICE_JOYPAD ; 
 int /*<<< orphan*/  core_set_controller_port_device (TYPE_1__*) ; 
 int /*<<< orphan*/  input_config_set_device (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ setting_generic_action_start_default (TYPE_2__*) ; 

__attribute__((used)) static int setting_action_start_libretro_device_type(rarch_setting_t *setting)
{
   retro_ctx_controller_info_t pad;
   unsigned port = 0;

   if (!setting || setting_generic_action_start_default(setting) != 0)
      return -1;

   port             = setting->index_offset;

   input_config_set_device(port, RETRO_DEVICE_JOYPAD);

   pad.port         = port;
   pad.device       = RETRO_DEVICE_JOYPAD;

   core_set_controller_port_device(&pad);

   return 0;
}