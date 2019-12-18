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
 int /*<<< orphan*/ * VEC_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fs_p ; 
 int /*<<< orphan*/ * input_file_stack ; 
 int /*<<< orphan*/  input_file_stack_history ; 
 int input_file_stack_restored ; 
 int input_file_stack_tick ; 

void
restore_input_file_stack (int tick)
{
  if (tick == 0)
    input_file_stack = NULL;
  else
    input_file_stack = VEC_index (fs_p, input_file_stack_history, tick - 1);
  input_file_stack_tick = tick;
  input_file_stack_restored = true;
}