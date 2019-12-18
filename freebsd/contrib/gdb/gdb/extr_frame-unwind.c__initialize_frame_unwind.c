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

/* Variables and functions */
 int /*<<< orphan*/  frame_unwind_data ; 
 int /*<<< orphan*/  frame_unwind_init ; 
 int /*<<< orphan*/  register_gdbarch_data (int /*<<< orphan*/ ) ; 

void
_initialize_frame_unwind (void)
{
  frame_unwind_data = register_gdbarch_data (frame_unwind_init);
}