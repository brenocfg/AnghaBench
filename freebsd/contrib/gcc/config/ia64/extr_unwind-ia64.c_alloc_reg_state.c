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
struct unw_reg_state {int dummy; } ;

/* Variables and functions */
 int atomic_alloc (int /*<<< orphan*/ *) ; 
 struct unw_reg_state* emergency_reg_state ; 
 int /*<<< orphan*/  emergency_reg_state_free ; 
 struct unw_reg_state* malloc (int) ; 
 int /*<<< orphan*/  reg_state_alloced ; 

__attribute__((used)) static struct unw_reg_state *
alloc_reg_state (void)
{
  struct unw_reg_state *rs;

#ifdef ENABLE_MALLOC_CHECKING
  reg_state_alloced++;
#endif

  rs = malloc (sizeof (struct unw_reg_state));
  if (!rs)
    {
      int n = atomic_alloc (&emergency_reg_state_free);
      if (n >= 0)
	rs = &emergency_reg_state[n];
    }

  return rs;
}