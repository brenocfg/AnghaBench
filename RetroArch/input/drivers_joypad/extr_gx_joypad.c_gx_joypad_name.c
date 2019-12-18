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

/* Variables and functions */
#define  WPAD_EXP_CLASSIC 131 
#define  WPAD_EXP_GAMECUBE 130 
#define  WPAD_EXP_NONE 129 
#define  WPAD_EXP_NUNCHUK 128 
 int* pad_type ; 

__attribute__((used)) static const char *gx_joypad_name(unsigned pad)
{
   switch (pad_type[pad])
   {
#ifdef HW_RVL
      case WPAD_EXP_NONE:
         return "Wiimote Controller";
      case WPAD_EXP_NUNCHUK:
         return "Nunchuk Controller";
      case WPAD_EXP_CLASSIC:
         return "Classic Controller";
#endif
      case WPAD_EXP_GAMECUBE:
         return "GameCube Controller";
   }

   return NULL;
}