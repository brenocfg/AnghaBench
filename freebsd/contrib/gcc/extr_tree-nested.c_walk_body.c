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
typedef  int /*<<< orphan*/  wi ;
typedef  int /*<<< orphan*/  walk_tree_fn ;
typedef  int /*<<< orphan*/  tree ;
struct walk_stmt_info {int val_only; struct nesting_info* info; int /*<<< orphan*/  callback; } ;
struct nesting_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct walk_stmt_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  walk_stmts (struct walk_stmt_info*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
walk_body (walk_tree_fn callback, struct nesting_info *info, tree *stmt_p)
{
  struct walk_stmt_info wi;

  memset (&wi, 0, sizeof (wi));
  wi.callback = callback;
  wi.info = info;
  wi.val_only = true;

  walk_stmts (&wi, stmt_p);
}