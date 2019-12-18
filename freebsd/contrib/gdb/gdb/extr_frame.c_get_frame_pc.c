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
struct frame_info {int /*<<< orphan*/ * next; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  frame_pc_unwind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 

CORE_ADDR
get_frame_pc (struct frame_info *frame)
{
  gdb_assert (frame->next != NULL);
  return frame_pc_unwind (frame->next);
}