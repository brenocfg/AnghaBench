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
struct unw_labeled_state {int dummy; } ;

/* Variables and functions */
 scalar_t__ PTR_IN (struct unw_labeled_state*,struct unw_labeled_state*) ; 
 int /*<<< orphan*/  atomic_free (int /*<<< orphan*/ *,struct unw_labeled_state*) ; 
 struct unw_labeled_state* emergency_labeled_state ; 
 int /*<<< orphan*/  emergency_labeled_state_free ; 
 int /*<<< orphan*/  free (struct unw_labeled_state*) ; 
 int /*<<< orphan*/  labeled_state_alloced ; 

__attribute__((used)) static void
free_label_state (struct unw_labeled_state *ls)
{
#ifdef ENABLE_MALLOC_CHECKING
  labeled_state_alloced--;
#endif

  if (PTR_IN (emergency_labeled_state, ls))
    atomic_free (&emergency_labeled_state_free, emergency_labeled_state - ls);
  else
    free (ls);
}