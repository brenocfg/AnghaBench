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
struct et_node {struct et_node* rightmost_occ; scalar_t__ father; struct et_node* son; } ;

/* Variables and functions */
 int /*<<< orphan*/  et_nodes ; 
 int /*<<< orphan*/  et_occurrences ; 
 int /*<<< orphan*/  et_split (struct et_node*) ; 
 int /*<<< orphan*/  pool_free (int /*<<< orphan*/ ,struct et_node*) ; 

void
et_free_tree (struct et_node *t)
{
  while (t->son)
    et_split (t->son);

  if (t->father)
    et_split (t);

  pool_free (et_occurrences, t->rightmost_occ);
  pool_free (et_nodes, t);
}