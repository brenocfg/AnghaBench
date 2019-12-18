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
 scalar_t__ cfun ; 
 int /*<<< orphan*/  end_sequence () ; 
 int /*<<< orphan*/  free_after_compilation (scalar_t__) ; 
 int /*<<< orphan*/  free_after_parsing (scalar_t__) ; 
 scalar_t__ in_sequence_p () ; 

void
expand_dummy_function_end (void)
{
  /* End any sequences that failed to be closed due to syntax errors.  */
  while (in_sequence_p ())
    end_sequence ();

  /* Outside function body, can't compute type's actual size
     until next function's body starts.  */

  free_after_parsing (cfun);
  free_after_compilation (cfun);
  cfun = 0;
}