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
 int FIRST_PSEUDO_REGISTER ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * modifies_mem_list ; 
 int /*<<< orphan*/  modifies_mem_obstack ; 
 int /*<<< orphan*/  modifies_mem_obstack_bottom ; 
 int /*<<< orphan*/  obstack_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_avail_info ; 

__attribute__((used)) static void
reset_opr_set_tables (void)
{
  memset (reg_avail_info, 0, FIRST_PSEUDO_REGISTER * sizeof (int));
  obstack_free (&modifies_mem_obstack, modifies_mem_obstack_bottom);
  modifies_mem_list = NULL;
}