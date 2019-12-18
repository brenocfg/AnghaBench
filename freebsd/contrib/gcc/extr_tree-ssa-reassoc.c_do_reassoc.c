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
 int /*<<< orphan*/  ENTRY_BLOCK_PTR ; 
 int /*<<< orphan*/  EXIT_BLOCK_PTR ; 
 int /*<<< orphan*/  break_up_subtract_bb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reassociate_bb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_reassoc (void)
{
  break_up_subtract_bb (ENTRY_BLOCK_PTR);
  reassociate_bb (EXIT_BLOCK_PTR);
}