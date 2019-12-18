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
typedef  int /*<<< orphan*/  HARD_REG_SET ;

/* Variables and functions */
 int FIRST_PSEUDO_REGISTER ; 
 scalar_t__ TEST_HARD_REG_BIT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dump_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
dump_hard_reg_set (HARD_REG_SET s)
{
  int reg;
  for (reg = 0; reg < FIRST_PSEUDO_REGISTER; reg++)
    if (TEST_HARD_REG_BIT (s, reg))
      fprintf (dump_file, " %d", reg);
}