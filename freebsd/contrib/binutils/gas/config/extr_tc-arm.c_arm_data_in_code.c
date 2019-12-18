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
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 scalar_t__ thumb_mode ; 

int
arm_data_in_code (void)
{
  if (thumb_mode && ! strncmp (input_line_pointer + 1, "data:", 5))
    {
      *input_line_pointer = '/';
      input_line_pointer += 5;
      *input_line_pointer = 0;
      return 1;
    }

  return 0;
}