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
 int get_absolute_expression () ; 
 char* input_line_pointer ; 

__attribute__((used)) static int
get_linefile_number (int *flag)
{
  SKIP_WHITESPACE ();

  if (*input_line_pointer < '0' || *input_line_pointer > '9')
    return 0;

  *flag = get_absolute_expression ();

  return 1;
}