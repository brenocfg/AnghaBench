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
struct ls_expr {int /*<<< orphan*/  stores; int /*<<< orphan*/  loads; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct ls_expr*) ; 
 int /*<<< orphan*/  free_INSN_LIST_list (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
free_ldst_entry (struct ls_expr * ptr)
{
  free_INSN_LIST_list (& ptr->loads);
  free_INSN_LIST_list (& ptr->stores);

  free (ptr);
}