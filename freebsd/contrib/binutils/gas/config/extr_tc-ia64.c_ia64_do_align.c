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
 char* input_line_pointer ; 
 int /*<<< orphan*/  s_align_bytes (int) ; 

__attribute__((used)) static void
ia64_do_align (int nbytes)
{
  char *saved_input_line_pointer = input_line_pointer;

  input_line_pointer = "";
  s_align_bytes (nbytes);
  input_line_pointer = saved_input_line_pointer;
}