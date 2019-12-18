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
struct frame_info {int /*<<< orphan*/  next; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  frame_unwind_address_in_block (int /*<<< orphan*/ ) ; 

CORE_ADDR
get_frame_address_in_block (struct frame_info *this_frame)
{
  return frame_unwind_address_in_block (this_frame->next);
}