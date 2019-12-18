#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int* port; } ;

/* Variables and functions */
#define  SCE_CTRL_TYPE_DS3 129 
#define  SCE_CTRL_TYPE_DS4 128 
 scalar_t__ SCE_KERNEL_MODEL_VITATV ; 
 TYPE_1__ curr_ctrl_info ; 
 scalar_t__ psp2_model ; 

__attribute__((used)) static const char *psp_joypad_name(unsigned pad)
{
#ifdef VITA
   if (psp2_model != SCE_KERNEL_MODEL_VITATV)
      return "Vita Controller";

   switch (curr_ctrl_info.port[pad + 1])
   {
      case SCE_CTRL_TYPE_DS3:
         return "DS3 Controller";
      case SCE_CTRL_TYPE_DS4:
         return "DS4 Controller";
      default:
         return "Unpaired";
   }
#else
   return "PSP Controller";
#endif
}