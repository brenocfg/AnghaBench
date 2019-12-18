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
 int /*<<< orphan*/  ECOFF_DEBUGGING ; 
 int /*<<< orphan*/  mips_nonecoff_pseudo_table ; 
 int /*<<< orphan*/  mips_pseudo_table ; 
 int /*<<< orphan*/  pop_insert (int /*<<< orphan*/ ) ; 

void
mips_pop_insert (void)
{
  pop_insert (mips_pseudo_table);
  if (! ECOFF_DEBUGGING)
    pop_insert (mips_nonecoff_pseudo_table);
}