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
 int /*<<< orphan*/  peephole2_optimize () ; 

__attribute__((used)) static unsigned int
rest_of_handle_peephole2 (void)
{
#ifdef HAVE_peephole2
  peephole2_optimize ();
#endif
  return 0;
}