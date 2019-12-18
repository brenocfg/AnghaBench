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
 int /*<<< orphan*/  bitmap_obstack_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_aux_for_blocks () ; 
 int /*<<< orphan*/  greg_obstack ; 

__attribute__((used)) static void
free_bb_info (void)
{
  bitmap_obstack_release (&greg_obstack); 
  free_aux_for_blocks ();
}