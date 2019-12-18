#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_5__ {int /*<<< orphan*/  is_negative; int /*<<< orphan*/  axis; } ;
typedef  TYPE_1__ axis_data ;
struct TYPE_7__ {int /*<<< orphan*/  (* get_axis_value ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* read_axis_data ) (scalar_t__,TYPE_1__*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  analog_state; } ;

/* Variables and functions */
 scalar_t__ AXIS_NONE ; 
 int /*<<< orphan*/  kpad_query_pad (unsigned int) ; 
 TYPE_4__ pad_functions ; 
 int /*<<< orphan*/  stub1 (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int to_wiimote_channel (unsigned int) ; 
 TYPE_2__* wiimotes ; 

__attribute__((used)) static int16_t kpad_axis(unsigned pad, uint32_t axis)
{
   axis_data data;
   int channel = to_wiimote_channel(pad);

   if (!kpad_query_pad(pad) || channel < 0 || axis == AXIS_NONE)
      return 0;

   pad_functions.read_axis_data(axis, &data);
   return pad_functions.get_axis_value(data.axis,
         wiimotes[channel].analog_state,
         data.is_negative);
}