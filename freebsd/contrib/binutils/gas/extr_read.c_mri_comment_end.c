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
 int /*<<< orphan*/  flag_mri ; 
 char* input_line_pointer ; 
 int /*<<< orphan*/ * is_end_of_line ; 
 int /*<<< orphan*/  know (int /*<<< orphan*/ ) ; 

void
mri_comment_end (char *stop, int stopc)
{
  know (flag_mri);

  input_line_pointer = stop;
  *stop = stopc;
  while (!is_end_of_line[(unsigned char) *input_line_pointer])
    ++input_line_pointer;
}