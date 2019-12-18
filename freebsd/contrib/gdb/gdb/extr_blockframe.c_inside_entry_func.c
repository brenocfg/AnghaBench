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
struct frame_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ entry_point_address () ; 
 scalar_t__ get_frame_func (struct frame_info*) ; 

int
inside_entry_func (struct frame_info *this_frame)
{
  return (get_frame_func (this_frame) == entry_point_address ());
}