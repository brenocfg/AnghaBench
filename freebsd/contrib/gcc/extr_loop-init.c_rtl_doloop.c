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
 scalar_t__ current_loops ; 
 int /*<<< orphan*/  doloop_optimize_loops (scalar_t__) ; 

__attribute__((used)) static unsigned int
rtl_doloop (void)
{
#ifdef HAVE_doloop_end
  if (current_loops)
    doloop_optimize_loops (current_loops);
#endif
  return 0;
}