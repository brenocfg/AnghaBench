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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {scalar_t__ axis; int is_negative; } ;
typedef  TYPE_1__ axis_data ;

/* Variables and functions */
 scalar_t__ AXIS_INVALID ; 
 scalar_t__ AXIS_NEG_GET (int /*<<< orphan*/ ) ; 
 scalar_t__ AXIS_POS_GET (int /*<<< orphan*/ ) ; 

void gamepad_read_axis_data(uint32_t axis, axis_data *data)
{
   if(!data)
      return;

   data->axis = AXIS_POS_GET(axis);
   data->is_negative = false;

   if(data->axis >= AXIS_INVALID)
   {
      data->axis = AXIS_NEG_GET(axis);
      data->is_negative = true;
   }
}