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
struct unw_reg_state {struct unw_reg_state* next; } ;

/* Variables and functions */
 struct unw_reg_state* alloc_reg_state () ; 
 int /*<<< orphan*/  memcpy (struct unw_reg_state*,struct unw_reg_state*,int) ; 

__attribute__((used)) static struct unw_reg_state *
dup_state_stack (struct unw_reg_state *rs)
{
  struct unw_reg_state *copy, *prev = NULL, *first = NULL;

  while (rs)
    {
      copy = alloc_reg_state ();
      memcpy (copy, rs, sizeof(*copy));
      if (first)
	prev->next = copy;
      else
	first = copy;
      rs = rs->next;
      prev = copy;
    }

  return first;
}