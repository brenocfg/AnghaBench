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
struct TYPE_2__ {int /*<<< orphan*/  dpad; } ;
struct ps4 {TYPE_1__ btn; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPAD_DOWN ; 
 int /*<<< orphan*/  DPAD_DOWN_LEFT ; 
 int /*<<< orphan*/  DPAD_LEFT ; 
 int /*<<< orphan*/  DPAD_LEFT_UP ; 
 int /*<<< orphan*/  DPAD_RIGHT ; 
 int /*<<< orphan*/  DPAD_RIGHT_DOWN ; 
 int /*<<< orphan*/  DPAD_UP ; 
 int /*<<< orphan*/  DPAD_UP_RIGHT ; 
#define  RETRO_DEVICE_ID_JOYPAD_DOWN 131 
#define  RETRO_DEVICE_ID_JOYPAD_LEFT 130 
#define  RETRO_DEVICE_ID_JOYPAD_RIGHT 129 
#define  RETRO_DEVICE_ID_JOYPAD_UP 128 

__attribute__((used)) static bool hidpad_ps4_check_dpad(struct ps4 *rpt, unsigned id)
{
   switch (id)
   {
      case RETRO_DEVICE_ID_JOYPAD_UP:
         return (rpt->btn.dpad == DPAD_LEFT_UP)    || (rpt->btn.dpad == DPAD_UP)    || (rpt->btn.dpad == DPAD_UP_RIGHT);
      case RETRO_DEVICE_ID_JOYPAD_RIGHT:
         return (rpt->btn.dpad == DPAD_UP_RIGHT)   || (rpt->btn.dpad == DPAD_RIGHT) || (rpt->btn.dpad == DPAD_RIGHT_DOWN);
      case RETRO_DEVICE_ID_JOYPAD_DOWN:
         return (rpt->btn.dpad == DPAD_RIGHT_DOWN) || (rpt->btn.dpad == DPAD_DOWN)  || (rpt->btn.dpad == DPAD_DOWN_LEFT);
      case RETRO_DEVICE_ID_JOYPAD_LEFT:
         return (rpt->btn.dpad == DPAD_DOWN_LEFT)  || (rpt->btn.dpad == DPAD_LEFT)  || (rpt->btn.dpad == DPAD_LEFT_UP);
   }

   return false;
}