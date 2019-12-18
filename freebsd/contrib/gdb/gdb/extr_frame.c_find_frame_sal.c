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
struct symtab_and_line {int dummy; } ;
struct frame_info {int dummy; } ;

/* Variables and functions */
 struct symtab_and_line find_pc_line (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_frame_pc (struct frame_info*) ; 
 int /*<<< orphan*/  pc_notcurrent (struct frame_info*) ; 

void
find_frame_sal (struct frame_info *frame, struct symtab_and_line *sal)
{
  (*sal) = find_pc_line (get_frame_pc (frame), pc_notcurrent (frame));
}