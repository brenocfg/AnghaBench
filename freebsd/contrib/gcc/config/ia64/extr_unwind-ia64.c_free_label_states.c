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
struct unw_labeled_state {int /*<<< orphan*/  saved_state; struct unw_labeled_state* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_label_state (struct unw_labeled_state*) ; 
 int /*<<< orphan*/  free_state_stack (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
free_label_states (struct unw_labeled_state *ls)
{
  struct unw_labeled_state *next;

  for (; ls ; ls = next)
    {
      next = ls->next;

      free_state_stack (&ls->saved_state);
      free_label_state (ls);
    }
}