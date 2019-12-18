#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_4__ {int /*<<< orphan*/  is_negative; int /*<<< orphan*/  axis; } ;
typedef  TYPE_1__ axis_data ;
struct TYPE_5__ {int /*<<< orphan*/  (* get_axis_value ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* read_axis_data ) (scalar_t__,TYPE_1__*) ;} ;

/* Variables and functions */
 scalar_t__ AXIS_NONE ; 
 int /*<<< orphan*/  analog_state ; 
 TYPE_3__ pad_functions ; 
 int /*<<< orphan*/  stub1 (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpad_query_pad (unsigned int) ; 

__attribute__((used)) static int16_t wpad_axis(unsigned pad, uint32_t axis)
{
   axis_data data;

   if (!wpad_query_pad(pad) || axis == AXIS_NONE)
      return 0;

   pad_functions.read_axis_data(axis, &data);
   return pad_functions.get_axis_value(data.axis, analog_state, data.is_negative);
}