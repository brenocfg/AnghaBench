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
struct TYPE_5__ {unsigned int pads_connected; TYPE_1__* pad_states; } ;
typedef  TYPE_2__ android_input_t ;
struct TYPE_4__ {int id; } ;

/* Variables and functions */
 int AINPUT_SOURCE_MOUSE ; 
 int AINPUT_SOURCE_TOUCHPAD ; 
 int AINPUT_SOURCE_TOUCHSCREEN ; 

__attribute__((used)) static int android_input_get_id_port(android_input_t *android, int id,
      int source)
{
   unsigned i;
   int ret = -1;
   if (source & (AINPUT_SOURCE_TOUCHSCREEN | AINPUT_SOURCE_MOUSE |
            AINPUT_SOURCE_TOUCHPAD))
         ret = 0; /* touch overlay is always user 1 */

   for (i = 0; i < android->pads_connected; i++)
   {
      if (android->pad_states[i].id == id)
      {
         ret = i;
         break;
      }
   }

   return ret;
}