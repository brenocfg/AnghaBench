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
 int no_new_pseudos ; 
 int /*<<< orphan*/  optimize_mode_switching () ; 

__attribute__((used)) static unsigned int
rest_of_handle_mode_switching (void)
{
#ifdef OPTIMIZE_MODE_SWITCHING
  no_new_pseudos = 0;
  optimize_mode_switching ();
  no_new_pseudos = 1;
#endif /* OPTIMIZE_MODE_SWITCHING */
  return 0;
}