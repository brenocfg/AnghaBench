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
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/ * heapvar_for_stmt ; 
 int /*<<< orphan*/  htab_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nonlocal_all ; 

void
delete_alias_heapvars (void)
{
  nonlocal_all = NULL_TREE;
  htab_delete (heapvar_for_stmt);
  heapvar_for_stmt = NULL;
}