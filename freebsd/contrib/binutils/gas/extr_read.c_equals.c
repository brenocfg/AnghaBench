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
 int /*<<< orphan*/  assign_symbol (char*,int) ; 
 int /*<<< orphan*/  demand_empty_rest_of_line () ; 
 scalar_t__ flag_mri ; 
 char* input_line_pointer ; 
 int /*<<< orphan*/  mri_comment_end (char*,char) ; 
 char* mri_comment_field (char*) ; 

void
equals (char *sym_name, int reassign)
{
  char *stop = NULL;
  char stopc = 0;

  input_line_pointer++;
  if (*input_line_pointer == '=')
    input_line_pointer++;
  if (reassign < 0 && *input_line_pointer == '=')
    input_line_pointer++;

  while (*input_line_pointer == ' ' || *input_line_pointer == '\t')
    input_line_pointer++;

  if (flag_mri)
    stop = mri_comment_field (&stopc);

  assign_symbol (sym_name, reassign >= 0 ? !reassign : reassign);

  if (flag_mri)
    {
      demand_empty_rest_of_line ();
      mri_comment_end (stop, stopc);
    }
}