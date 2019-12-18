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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  htab_t ;

/* Variables and functions */
 int /*<<< orphan*/  htab_create (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htab_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htab_eq_pointer ; 
 int /*<<< orphan*/  htab_hash_pointer ; 
 int /*<<< orphan*/  verify_stmt_tree_r ; 
 int /*<<< orphan*/  walk_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
verify_stmt_tree (tree t)
{
  htab_t statements;
  statements = htab_create (37, htab_hash_pointer, htab_eq_pointer, NULL);
  walk_tree (&t, verify_stmt_tree_r, &statements, NULL);
  htab_delete (statements);
}