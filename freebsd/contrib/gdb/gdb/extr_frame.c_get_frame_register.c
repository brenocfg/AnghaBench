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

/* Variables and functions */
 int /*<<< orphan*/  frame_unwind_register (int /*<<< orphan*/ ,int,void*) ; 

void
get_frame_register (struct frame_info *frame,
		    int regnum, void *buf)
{
  frame_unwind_register (frame->next, regnum, buf);
}