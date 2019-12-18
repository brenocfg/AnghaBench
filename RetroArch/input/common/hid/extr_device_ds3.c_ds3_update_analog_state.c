#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int int16_t ;
struct TYPE_3__ {int* data; int** analog_state; } ;
typedef  TYPE_1__ ds3_instance_t ;

/* Variables and functions */

__attribute__((used)) static void ds3_update_analog_state(ds3_instance_t *instance)
{
   int pad_axis;
   int16_t interpolated;
   unsigned stick, axis;

   for(pad_axis = 0; pad_axis < 4; pad_axis++)
   {
      axis = pad_axis % 2 ? 0 : 1;
      stick = pad_axis / 2;
      interpolated = instance->data[6+pad_axis];
      instance->analog_state[stick][axis] = (interpolated - 128) * 256;
   }
}