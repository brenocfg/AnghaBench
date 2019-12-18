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
 int /*<<< orphan*/  expr_obstack ; 
 int /*<<< orphan*/  expr_table ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htab_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  modifies_mem_obstack ; 
 int /*<<< orphan*/  obstack_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  occr_obstack ; 
 int /*<<< orphan*/  reg_avail_info ; 
 int /*<<< orphan*/  uid_cuid ; 
 int /*<<< orphan*/  unoccr_obstack ; 

__attribute__((used)) static void
free_mem (void)
{
  free (uid_cuid);

  htab_delete (expr_table);

  obstack_free (&expr_obstack, NULL);
  obstack_free (&occr_obstack, NULL);
  obstack_free (&unoccr_obstack, NULL);
  obstack_free (&modifies_mem_obstack, NULL);

  free (reg_avail_info);
}