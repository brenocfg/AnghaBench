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

__attribute__((used)) static unsigned
determine_split_iv_delta (unsigned n_copy, unsigned n_copies, bool unrolling)
{
  if (unrolling)
    {
      /* If we are unrolling, initialization is done in the original loop
	 body (number 0).  */
      return n_copy;
    }
  else
    {
      /* If we are peeling, the copy in that the initialization occurs has
	 number 1.  The original loop (number 0) is the last.  */
      if (n_copy)
	return n_copy - 1;
      else
	return n_copies;
    }
}