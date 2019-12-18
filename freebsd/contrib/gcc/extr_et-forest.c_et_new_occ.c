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
struct et_occ {scalar_t__ min; struct et_occ* min_occ; scalar_t__ depth; int /*<<< orphan*/ * next; int /*<<< orphan*/ * prev; int /*<<< orphan*/ * parent; struct et_node* of; } ;
struct et_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ create_alloc_pool (char*,int,int) ; 
 scalar_t__ et_occurrences ; 
 struct et_occ* pool_alloc (scalar_t__) ; 

__attribute__((used)) static struct et_occ *
et_new_occ (struct et_node *node)
{
  struct et_occ *nw;
  
  if (!et_occurrences)
    et_occurrences = create_alloc_pool ("et_occ pool", sizeof (struct et_occ), 300);
  nw = pool_alloc (et_occurrences);

  nw->of = node;
  nw->parent = NULL;
  nw->prev = NULL;
  nw->next = NULL;

  nw->depth = 0;
  nw->min_occ = nw;
  nw->min = 0;

  return nw;
}