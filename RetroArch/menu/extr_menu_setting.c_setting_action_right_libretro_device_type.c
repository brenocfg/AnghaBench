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
struct TYPE_5__ {unsigned int port; unsigned int device; } ;
typedef  TYPE_1__ retro_ctx_controller_info_t ;
struct TYPE_6__ {unsigned int index_offset; } ;
typedef  TYPE_2__ rarch_setting_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (unsigned int*) ; 
 int /*<<< orphan*/  core_set_controller_port_device (TYPE_1__*) ; 
 unsigned int input_config_get_device (unsigned int) ; 
 int /*<<< orphan*/  input_config_set_device (unsigned int,unsigned int) ; 
 unsigned int libretro_device_get_size (unsigned int*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int setting_action_right_libretro_device_type(
      rarch_setting_t *setting, bool wraparound)
{
   retro_ctx_controller_info_t pad;
   unsigned current_device, current_idx, i, devices[128],
            types = 0, port = 0;

   if (!setting)
      return -1;

   port           = setting->index_offset;
   types          = libretro_device_get_size(devices, ARRAY_SIZE(devices), port);
   current_device = input_config_get_device(port);
   current_idx    = 0;
   for (i = 0; i < types; i++)
   {
      if (current_device != devices[i])
         continue;

      current_idx = i;
      break;
   }

   current_device = devices
      [(current_idx + 1) % types];

   input_config_set_device(port, current_device);

   pad.port   = port;
   pad.device = current_device;

   core_set_controller_port_device(&pad);

   return 0;
}