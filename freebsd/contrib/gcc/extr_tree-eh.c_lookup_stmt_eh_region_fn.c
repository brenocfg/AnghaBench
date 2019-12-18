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
struct throw_stmt_node {int region_nr; int /*<<< orphan*/  stmt; } ;
struct function {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_eh_throw_stmt_table (struct function*) ; 
 scalar_t__ htab_find (int /*<<< orphan*/ ,struct throw_stmt_node*) ; 

int
lookup_stmt_eh_region_fn (struct function *ifun, tree t)
{
  struct throw_stmt_node *p, n;

  if (!get_eh_throw_stmt_table (ifun))
    return -2;

  n.stmt = t;
  p = (struct throw_stmt_node *) htab_find (get_eh_throw_stmt_table (ifun),
                                            &n);

  return (p ? p->region_nr : -1);
}