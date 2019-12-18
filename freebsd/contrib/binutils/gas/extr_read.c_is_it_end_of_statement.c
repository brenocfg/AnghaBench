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
 int /*<<< orphan*/  SKIP_WHITESPACE () ; 
 scalar_t__* input_line_pointer ; 
 int* is_end_of_line ; 

int
is_it_end_of_statement (void)
{
  SKIP_WHITESPACE ();
  return (is_end_of_line[(unsigned char) *input_line_pointer]);
}