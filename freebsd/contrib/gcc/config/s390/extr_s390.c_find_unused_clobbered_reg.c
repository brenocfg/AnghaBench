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
 int /*<<< orphan*/ * regs_ever_live ; 

__attribute__((used)) static int
find_unused_clobbered_reg (void)
{
  int i;
  for (i = 0; i < 6; i++)
    if (!regs_ever_live[i])
      return i;
  return 0;
}