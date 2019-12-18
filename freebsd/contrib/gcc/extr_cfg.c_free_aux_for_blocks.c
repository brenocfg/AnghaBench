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
 int /*<<< orphan*/  block_aux_obstack ; 
 int /*<<< orphan*/  clear_aux_for_blocks () ; 
 int /*<<< orphan*/ * first_block_aux_obj ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obstack_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
free_aux_for_blocks (void)
{
  gcc_assert (first_block_aux_obj);
  obstack_free (&block_aux_obstack, first_block_aux_obj);
  first_block_aux_obj = NULL;

  clear_aux_for_blocks ();
}