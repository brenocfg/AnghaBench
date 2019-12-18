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
 scalar_t__* buffer_limit ; 
 scalar_t__* input_line_pointer ; 
 int /*<<< orphan*/ * is_end_of_line ; 
 int /*<<< orphan*/  know (int /*<<< orphan*/ ) ; 

void
ignore_rest_of_line (void)
{
  while (input_line_pointer < buffer_limit
	 && !is_end_of_line[(unsigned char) *input_line_pointer])
    input_line_pointer++;

  input_line_pointer++;

  /* Return pointing just after end-of-line.  */
  know (is_end_of_line[(unsigned char) input_line_pointer[-1]]);
}