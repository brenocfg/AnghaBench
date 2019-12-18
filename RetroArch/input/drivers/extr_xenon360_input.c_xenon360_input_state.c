#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint64_t ;
struct retro_keybind {int joykey; } ;
typedef  int /*<<< orphan*/  rarch_joypad_info_t ;
typedef  int int16_t ;

/* Variables and functions */
 int DEFAULT_MAX_PADS ; 
 unsigned int RARCH_FIRST_CUSTOM_BIND ; 
 unsigned int RETRO_DEVICE_ID_JOYPAD_MASK ; 
#define  RETRO_DEVICE_JOYPAD 128 
 int* state ; 

__attribute__((used)) static int16_t xenon360_input_state(void *data,
      rarch_joypad_info_t joypad_info,
      const struct retro_keybind **binds,
      bool port, unsigned device,
      unsigned idx, unsigned id)
{
   uint64_t button            = binds[port][id].joykey;

   if (port >= DEFAULT_MAX_PADS)
      return 0;

   switch (device)
   {
      case RETRO_DEVICE_JOYPAD:
         if (id == RETRO_DEVICE_ID_JOYPAD_MASK)
         {
            unsigned i;
            int16_t ret = 0;

            for (i = 0; i < RARCH_FIRST_CUSTOM_BIND; i++)
            {
               if (state[port] & binds[port][i].joykey)
                  ret |= (1 << i);
            }

            return ret;
         }
         else
            if (state[port] & binds[port][id].joykey)
               return true;
         break;
      default:
         break;
   }

   return 0;
}