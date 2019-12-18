#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  enum retro_rumble_effect { ____Placeholder_retro_rumble_effect } retro_rumble_effect ;
struct TYPE_5__ {int /*<<< orphan*/ * port; } ;
struct TYPE_4__ {int small; void* large; } ;

/* Variables and functions */
 void* LERP (int,int,int) ; 
#define  RETRO_RUMBLE_DUMMY 132 
#define  RETRO_RUMBLE_STRONG 131 
#define  RETRO_RUMBLE_WEAK 130 
#define  SCE_CTRL_TYPE_DS3 129 
#define  SCE_CTRL_TYPE_DS4 128 
 scalar_t__ SCE_KERNEL_MODEL_VITATV ; 
 TYPE_1__* actuators ; 
 TYPE_2__ curr_ctrl_info ; 
 scalar_t__ psp2_model ; 
 int /*<<< orphan*/  sceCtrlSetActuator (unsigned int,TYPE_1__*) ; 

__attribute__((used)) static bool psp_joypad_rumble(unsigned pad,
      enum retro_rumble_effect effect, uint16_t strength)
{
#ifdef VITA
   if (psp2_model != SCE_KERNEL_MODEL_VITATV)
      return false;

   switch (effect)
   {
      case RETRO_RUMBLE_WEAK:
         switch (curr_ctrl_info.port[pad + 1])
         {
            case SCE_CTRL_TYPE_DS3:
               actuators[pad].small = strength > 1 ? 1 : 0;
               break;
            case SCE_CTRL_TYPE_DS4:
               actuators[pad].small = LERP(strength, 0xffff, 0xff);
               break;
            default:
               actuators[pad].small = 0;
         }
         break;
      case RETRO_RUMBLE_STRONG:
         switch (curr_ctrl_info.port[pad + 1])
         {
            case SCE_CTRL_TYPE_DS3:
               actuators[pad].large = strength > 1 ? LERP(strength, 0xffff, 0xbf) + 0x40 : 0;
               break;
            case SCE_CTRL_TYPE_DS4:
               actuators[pad].large = LERP(strength, 0xffff, 0xff);
               break;
            default:
               actuators[pad].large = 0;
         }
         break;
      case RETRO_RUMBLE_DUMMY:
      default:
         break;
   }
   sceCtrlSetActuator(pad + 1, &actuators[pad]);

   return true;
#else
   return false;
#endif
}