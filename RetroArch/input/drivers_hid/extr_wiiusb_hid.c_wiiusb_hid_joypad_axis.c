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
struct TYPE_2__ {int /*<<< orphan*/ * connections; } ;
typedef  TYPE_1__ wiiusb_hid_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ int16_t ;

/* Variables and functions */
 int AXIS_NEG_GET (scalar_t__) ; 
 scalar_t__ AXIS_NONE ; 
 int AXIS_POS_GET (scalar_t__) ; 
 scalar_t__ pad_connection_get_axis (int /*<<< orphan*/ *,unsigned int,int) ; 

__attribute__((used)) static int16_t wiiusb_hid_joypad_axis(void *data,
      unsigned port, uint32_t joyaxis)
{
   int16_t       val = 0;
   wiiusb_hid_t *hid = (wiiusb_hid_t*)data;

   if (joyaxis == AXIS_NONE)
      return 0;

   if (AXIS_NEG_GET(joyaxis) < 4)
   {
      val = pad_connection_get_axis(&hid->connections[port],
            port, AXIS_NEG_GET(joyaxis));

      if (val >= 0)
         val = 0;
   }
   else if (AXIS_POS_GET(joyaxis) < 4)
   {
      val = pad_connection_get_axis(&hid->connections[port],
            port, AXIS_POS_GET(joyaxis));

      if (val <= 0)
         val = 0;
   }

   return val;
}