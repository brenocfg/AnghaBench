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
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_warn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  demand_empty_rest_of_line () ; 
 void* get_absolute_expression () ; 
 char* input_line_pointer ; 
 int paper_height ; 
 void* paper_width ; 

void
listing_psize (int width_only)
{
  if (! width_only)
    {
      paper_height = get_absolute_expression ();

      if (paper_height < 0 || paper_height > 1000)
	{
	  paper_height = 0;
	  as_warn (_("strange paper height, set to no form"));
	}

      if (*input_line_pointer != ',')
	{
	  demand_empty_rest_of_line ();
	  return;
	}

      ++input_line_pointer;
    }

  paper_width = get_absolute_expression ();

  demand_empty_rest_of_line ();
}