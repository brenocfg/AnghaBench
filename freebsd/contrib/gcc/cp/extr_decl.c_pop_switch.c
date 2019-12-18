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
struct cp_switch {struct cp_switch* next; int /*<<< orphan*/  cases; int /*<<< orphan*/  switch_stmt; } ;
typedef  int /*<<< orphan*/  location_t ;

/* Variables and functions */
 scalar_t__ EXPR_HAS_LOCATION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXPR_LOCATION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SWITCH_STMT_COND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SWITCH_STMT_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_do_switch_warnings (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct cp_switch*) ; 
 int /*<<< orphan*/  input_location ; 
 int /*<<< orphan*/  processing_template_decl ; 
 int /*<<< orphan*/  splay_tree_delete (int /*<<< orphan*/ ) ; 
 struct cp_switch* switch_stack ; 

void
pop_switch (void)
{
  struct cp_switch *cs = switch_stack;
  location_t switch_location;

  /* Emit warnings as needed.  */
  if (EXPR_HAS_LOCATION (cs->switch_stmt))
    switch_location = EXPR_LOCATION (cs->switch_stmt);
  else
    switch_location = input_location;
  if (!processing_template_decl)
    c_do_switch_warnings (cs->cases, switch_location,
			  SWITCH_STMT_TYPE (cs->switch_stmt),
			  SWITCH_STMT_COND (cs->switch_stmt));

  splay_tree_delete (cs->cases);
  switch_stack = switch_stack->next;
  free (cs);
}