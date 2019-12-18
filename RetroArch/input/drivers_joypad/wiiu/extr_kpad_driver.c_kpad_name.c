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
struct TYPE_2__ {int type; } ;

/* Variables and functions */
 char const* PAD_NAME_CLASSIC ; 
 char const* PAD_NAME_NUNCHUK ; 
 char const* PAD_NAME_WIIMOTE ; 
 char const* PAD_NAME_WIIU_PRO ; 
 int /*<<< orphan*/  RARCH_LOG (char*,int) ; 
#define  WIIMOTE_TYPE_CLASSIC 132 
#define  WIIMOTE_TYPE_NONE 131 
#define  WIIMOTE_TYPE_NUNCHUK 130 
#define  WIIMOTE_TYPE_PRO 129 
#define  WIIMOTE_TYPE_WIIPLUS 128 
 int to_wiimote_channel (unsigned int) ; 
 TYPE_1__* wiimotes ; 

__attribute__((used)) static const char *kpad_name(unsigned pad)
{
   int channel = to_wiimote_channel(pad);
   if (channel < 0)
      return "unknown";

   switch(wiimotes[channel].type)
   {
      case WIIMOTE_TYPE_PRO:
         return PAD_NAME_WIIU_PRO;
      case WIIMOTE_TYPE_CLASSIC:
         return PAD_NAME_CLASSIC;
      case WIIMOTE_TYPE_NUNCHUK:
         return PAD_NAME_NUNCHUK;
      case WIIMOTE_TYPE_WIIPLUS:
         return PAD_NAME_WIIMOTE;
      case WIIMOTE_TYPE_NONE:
      default:
         RARCH_LOG("[kpad]: Unknown pad type %d\n", wiimotes[pad].type);
         break;
   }

   return "N/A";
}