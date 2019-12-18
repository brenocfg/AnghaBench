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
struct retro_controller_description {char* desc; } ;
struct TYPE_6__ {unsigned int size; int /*<<< orphan*/ * data; } ;
struct TYPE_7__ {TYPE_1__ ports; } ;
typedef  TYPE_2__ rarch_system_info_t ;
struct TYPE_8__ {unsigned int index_offset; } ;
typedef  TYPE_3__ rarch_setting_t ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_NONE ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_RETROPAD ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_RETROPAD_WITH_ANALOG ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_UNKNOWN ; 
#define  RETRO_DEVICE_ANALOG 130 
#define  RETRO_DEVICE_JOYPAD 129 
#define  RETRO_DEVICE_NONE 128 
 unsigned int input_config_get_device (unsigned int) ; 
 struct retro_controller_description* libretro_find_controller_description (int /*<<< orphan*/ *,unsigned int) ; 
 char* msg_hash_to_str (int /*<<< orphan*/ ) ; 
 TYPE_2__* runloop_get_system_info () ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 

__attribute__((used)) static void setting_get_string_representation_uint_libretro_device(
      rarch_setting_t *setting,
      char *s, size_t len)
{
   unsigned index_offset, device;
   const struct retro_controller_description *desc = NULL;
   const char *name            = NULL;
   rarch_system_info_t *system = runloop_get_system_info();

   if (!setting)
      return;

   index_offset                = setting->index_offset;
   device                      = input_config_get_device(index_offset);

   if (system)
   {
      if (index_offset < system->ports.size)
         desc = libretro_find_controller_description(
               &system->ports.data[index_offset],
               device);
   }

   if (desc)
      name = desc->desc;

   if (!name)
   {
      /* Find generic name. */
      switch (device)
      {
         case RETRO_DEVICE_NONE:
            name = msg_hash_to_str(MENU_ENUM_LABEL_VALUE_NONE);
            break;
         case RETRO_DEVICE_JOYPAD:
            name = msg_hash_to_str(MENU_ENUM_LABEL_VALUE_RETROPAD);
            break;
         case RETRO_DEVICE_ANALOG:
            name = msg_hash_to_str(MENU_ENUM_LABEL_VALUE_RETROPAD_WITH_ANALOG);
            break;
         default:
            name = msg_hash_to_str(MENU_ENUM_LABEL_VALUE_UNKNOWN);
            break;
      }
   }

   if (!string_is_empty(name))
      strlcpy(s, name, len);
}