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
 int UAP_PEEL ; 
 int UAP_UNROLL ; 
 int UAP_UNROLL_ALL ; 
 scalar_t__ current_loops ; 
 scalar_t__ flag_peel_loops ; 
 scalar_t__ flag_unroll_all_loops ; 
 scalar_t__ flag_unroll_loops ; 
 int /*<<< orphan*/  unroll_and_peel_loops (scalar_t__,int) ; 

__attribute__((used)) static unsigned int
rtl_unroll_and_peel_loops (void)
{
  if (current_loops)
    {
      int flags = 0;

      if (flag_peel_loops)
	flags |= UAP_PEEL;
      if (flag_unroll_loops)
	flags |= UAP_UNROLL;
      if (flag_unroll_all_loops)
	flags |= UAP_UNROLL_ALL;

      unroll_and_peel_loops (current_loops, flags);
    }
  return 0;
}