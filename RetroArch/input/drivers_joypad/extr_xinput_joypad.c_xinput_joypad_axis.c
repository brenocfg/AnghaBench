#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int int16_t ;
struct TYPE_6__ {int sThumbLX; int sThumbLY; int sThumbRX; int sThumbRY; int bLeftTrigger; int bRightTrigger; } ;
typedef  TYPE_2__ XINPUT_GAMEPAD ;
struct TYPE_8__ {int (* axis ) (unsigned int,scalar_t__) ;} ;
struct TYPE_5__ {TYPE_2__ Gamepad; } ;
struct TYPE_7__ {TYPE_1__ xstate; int /*<<< orphan*/  connected; } ;

/* Variables and functions */
 int AXIS_NEG_GET (scalar_t__) ; 
 scalar_t__ AXIS_NONE ; 
 int AXIS_POS_GET (scalar_t__) ; 
 TYPE_4__ dinput_joypad ; 
 TYPE_3__* g_xinput_states ; 
 int pad_index_to_xuser_index (unsigned int) ; 
 int stub1 (unsigned int,scalar_t__) ; 

__attribute__((used)) static int16_t xinput_joypad_axis (unsigned port_num, uint32_t joyaxis)
{
   int xuser;
   int16_t val         = 0;
   int     axis        = -1;
   bool is_neg         = false;
   bool is_pos         = false;
   XINPUT_GAMEPAD* pad = NULL;

   if (joyaxis == AXIS_NONE)
      return 0;

   xuser = pad_index_to_xuser_index(port_num);

#ifdef HAVE_DINPUT
   if (xuser == -1)
      return dinput_joypad.axis(port_num, joyaxis);
#endif

   if (!(g_xinput_states[xuser].connected))
      return 0;

   /* triggers (axes 4,5) cannot be negative */
   if (AXIS_NEG_GET(joyaxis) <= 3)
   {
      axis = AXIS_NEG_GET(joyaxis);
      is_neg = true;
   }
   else if (AXIS_POS_GET(joyaxis) <= 5)
   {
      axis = AXIS_POS_GET(joyaxis);
      is_pos = true;
   }

   pad = &(g_xinput_states[xuser].xstate.Gamepad);

   switch (axis)
   {
      case 0:
         val = pad->sThumbLX;
         break;
      case 1:
         val = pad->sThumbLY;
         break;
      case 2:
         val = pad->sThumbRX;
         break;
      case 3:
         val = pad->sThumbRY;
         break;
      case 4:
         val = pad->bLeftTrigger  * 32767 / 255;
         break; /* map 0..255 to 0..32767 */
      case 5:
         val = pad->bRightTrigger * 32767 / 255;
         break;
   }

   if (is_neg && val > 0)
      val = 0;
   else if (is_pos && val < 0)
      val = 0;

   /* Clamp to avoid overflow error. */
   if (val == -32768)
      val = -32767;

   return val;
}