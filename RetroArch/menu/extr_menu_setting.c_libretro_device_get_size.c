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
struct retro_controller_info {unsigned int num_types; TYPE_2__* types; } ;
struct TYPE_5__ {unsigned int size; struct retro_controller_info* data; } ;
struct TYPE_7__ {TYPE_1__ ports; } ;
typedef  TYPE_3__ rarch_system_info_t ;
struct TYPE_6__ {unsigned int id; } ;

/* Variables and functions */
 unsigned int RETRO_DEVICE_ANALOG ; 
 unsigned int RETRO_DEVICE_JOYPAD ; 
 unsigned int RETRO_DEVICE_NONE ; 
 TYPE_3__* runloop_get_system_info () ; 

__attribute__((used)) static unsigned libretro_device_get_size(unsigned *devices, size_t devices_size, unsigned port)
{
   unsigned types                           = 0;
   const struct retro_controller_info *desc = NULL;
   rarch_system_info_t              *system = runloop_get_system_info();

   devices[types++]                         = RETRO_DEVICE_NONE;
   devices[types++]                         = RETRO_DEVICE_JOYPAD;

   if (system)
   {
      /* Only push RETRO_DEVICE_ANALOG as default if we use an
       * older core which doesn't use SET_CONTROLLER_INFO. */
      if (!system->ports.size)
         devices[types++] = RETRO_DEVICE_ANALOG;

      if (port < system->ports.size)
         desc = &system->ports.data[port];
   }

   if (desc)
   {
      unsigned i;
      for (i = 0; i < desc->num_types; i++)
      {
         unsigned id = desc->types[i].id;
         if (types < devices_size &&
               id != RETRO_DEVICE_NONE &&
               id != RETRO_DEVICE_JOYPAD)
            devices[types++] = id;
      }
   }

   return types;
}