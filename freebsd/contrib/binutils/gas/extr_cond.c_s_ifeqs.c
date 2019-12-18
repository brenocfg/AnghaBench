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
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cond_obstack ; 
 struct conditional_frame* current_cframe ; 
 char* demand_copy_C_string (int*) ; 
 int /*<<< orphan*/  demand_empty_rest_of_line () ; 
 int /*<<< orphan*/  ignore_rest_of_line () ; 
 int /*<<< orphan*/  initialize_cframe (struct conditional_frame*) ; 
 char* input_line_pointer ; 
 int /*<<< orphan*/  listing_list (int) ; 
 scalar_t__ obstack_copy (int /*<<< orphan*/ *,struct conditional_frame*,int) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

void
s_ifeqs (int arg)
{
  char *s1, *s2;
  int len1, len2;
  int res;
  struct conditional_frame cframe;

  s1 = demand_copy_C_string (&len1);

  SKIP_WHITESPACE ();
  if (*input_line_pointer != ',')
    {
      as_bad (_(".ifeqs syntax error"));
      ignore_rest_of_line ();
      return;
    }

  ++input_line_pointer;

  s2 = demand_copy_C_string (&len2);

  res = len1 == len2 && strncmp (s1, s2, len1) == 0;

  initialize_cframe (&cframe);
  cframe.ignoring = cframe.dead_tree || ! (res ^ arg);
  current_cframe = ((struct conditional_frame *)
		    obstack_copy (&cond_obstack, &cframe, sizeof (cframe)));

  if (LISTING_SKIP_COND ()
      && cframe.ignoring
      && (cframe.previous_cframe == NULL
	  || ! cframe.previous_cframe->ignoring))
    listing_list (2);

  demand_empty_rest_of_line ();
}