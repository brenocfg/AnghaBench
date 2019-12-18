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
 int constraint_len (char const*,int) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

__attribute__((used)) static void
check_constraint_len (void)
{
  const char *p;
  int d;

  for (p = ",#*+=&%!1234567890"; *p; p++)
    for (d = -9; d < 9; d++)
      gcc_assert (constraint_len (p, d) == d);
}