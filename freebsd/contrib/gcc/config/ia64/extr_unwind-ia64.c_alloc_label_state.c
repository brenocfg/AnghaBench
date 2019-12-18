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
 int atomic_alloc (int /*<<< orphan*/ *) ; 
 struct unw_labeled_state* emergency_labeled_state ; 
 int /*<<< orphan*/  emergency_labeled_state_free ; 
 int /*<<< orphan*/  labeled_state_alloced ; 
 struct unw_labeled_state* malloc (int) ; 

__attribute__((used)) static struct unw_labeled_state *
alloc_label_state (void)
{
  struct unw_labeled_state *ls;

#ifdef ENABLE_MALLOC_CHECKING
  labeled_state_alloced++;
#endif

  ls = malloc(sizeof(struct unw_labeled_state));
  if (!ls)
    {
      int n = atomic_alloc (&emergency_labeled_state_free);
      if (n >= 0)
	ls = &emergency_labeled_state[n];
    }

  return ls;
}