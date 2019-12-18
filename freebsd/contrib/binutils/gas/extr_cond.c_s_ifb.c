#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct conditional_frame {int ignoring; TYPE_1__* previous_cframe; scalar_t__ dead_tree; } ;
typedef  int /*<<< orphan*/  cframe ;
struct TYPE_2__ {int /*<<< orphan*/  ignoring; } ;

/* Variables and functions */
 scalar_t__ LISTING_SKIP_COND () ; 
 int /*<<< orphan*/  SKIP_WHITESPACE () ; 
 int /*<<< orphan*/  cond_obstack ; 
 struct conditional_frame* current_cframe ; 
 int /*<<< orphan*/  ignore_rest_of_line () ; 
 int /*<<< orphan*/  initialize_cframe (struct conditional_frame*) ; 
 scalar_t__* input_line_pointer ; 
 int* is_end_of_line ; 
 int /*<<< orphan*/  listing_list (int) ; 
 scalar_t__ obstack_copy (int /*<<< orphan*/ *,struct conditional_frame*,int) ; 

void
s_ifb (int test_blank)
{
  struct conditional_frame cframe;

  initialize_cframe (&cframe);
  
  if (cframe.dead_tree)
    cframe.ignoring = 1;
  else
    {
      int is_eol;

      SKIP_WHITESPACE ();
      is_eol = is_end_of_line[(unsigned char) *input_line_pointer];
      cframe.ignoring = (test_blank == !is_eol);
    }

  current_cframe = ((struct conditional_frame *)
		    obstack_copy (&cond_obstack, &cframe,
				  sizeof (cframe)));

  if (LISTING_SKIP_COND ()
      && cframe.ignoring
      && (cframe.previous_cframe == NULL
	  || ! cframe.previous_cframe->ignoring))
    listing_list (2);

  ignore_rest_of_line ();
}