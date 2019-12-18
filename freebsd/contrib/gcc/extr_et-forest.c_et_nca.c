#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct et_occ {int depth; int min; struct et_node* of; TYPE_1__* min_occ; struct et_occ* parent; struct et_occ* prev; struct et_occ* next; } ;
struct et_node {struct et_occ* rightmost_occ; } ;
struct TYPE_2__ {struct et_node* of; } ;

/* Variables and functions */
 int /*<<< orphan*/  et_check_tree_sanity (struct et_occ*) ; 
 int /*<<< orphan*/  et_splay (struct et_occ*) ; 
 int /*<<< orphan*/  set_next (struct et_occ*,struct et_occ*) ; 
 int /*<<< orphan*/  set_prev (struct et_occ*,struct et_occ*) ; 

struct et_node *
et_nca (struct et_node *n1, struct et_node *n2)
{
  struct et_occ *o1 = n1->rightmost_occ, *o2 = n2->rightmost_occ, *om;
  struct et_occ *l, *r, *ret;
  int mn;

  if (n1 == n2)
    return n1;

  et_splay (o1);
  l = o1->prev;
  r = o1->next;
  if (l)
    l->parent = NULL;
  if (r)
    r->parent = NULL;
  et_splay (o2);

  if (l == o2 || (l && l->parent != NULL))
    {
      ret = o2->next;

      set_prev (o1, o2);
      if (r)
	r->parent = o1;
    }
  else
    {
      ret = o2->prev;

      set_next (o1, o2);
      if (l)
	l->parent = o1;
    }

  if (0 < o2->depth)
    {
      om = o1;
      mn = o1->depth;
    }
  else
    {
      om = o2;
      mn = o2->depth + o1->depth;
    }

#ifdef DEBUG_ET
  et_check_tree_sanity (o2);
#endif

  if (ret && ret->min + o1->depth + o2->depth < mn)
    return ret->min_occ->of;
  else
    return om->of;
}