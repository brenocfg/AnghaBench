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
 int /*<<< orphan*/  clobber_return_register () ; 
 int /*<<< orphan*/  expand_null_return_1 () ; 

void
expand_null_return (void)
{
  /* If this function was declared to return a value, but we
     didn't, clobber the return registers so that they are not
     propagated live to the rest of the function.  */
  clobber_return_register ();

  expand_null_return_1 ();
}