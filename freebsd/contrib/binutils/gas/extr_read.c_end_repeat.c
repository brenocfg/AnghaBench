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
 int /*<<< orphan*/  buffer_limit ; 
 int /*<<< orphan*/  cond_exit_macro (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_line_pointer ; 
 int /*<<< orphan*/  input_scrub_next_buffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  macro_nest ; 

void
end_repeat (int extra)
{
  cond_exit_macro (macro_nest);
  while (extra-- >= 0)
    buffer_limit = input_scrub_next_buffer (&input_line_pointer);
}