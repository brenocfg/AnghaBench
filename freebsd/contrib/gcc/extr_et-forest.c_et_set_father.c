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
struct et_occ {scalar_t__ depth; scalar_t__ min; int /*<<< orphan*/  min_occ; struct et_occ* prev; } ;
struct et_node {struct et_node* son; struct et_node* right; struct et_node* left; struct et_node* father; struct et_occ* parent_occ; struct et_occ* rightmost_occ; } ;

/* Variables and functions */
 int /*<<< orphan*/  et_check_tree_sanity (struct et_occ*) ; 
 struct et_occ* et_new_occ (struct et_node*) ; 
 int /*<<< orphan*/  et_recomp_min (struct et_occ*) ; 
 int /*<<< orphan*/  et_splay (struct et_occ*) ; 
 int /*<<< orphan*/  record_path_before (struct et_occ*) ; 
 int /*<<< orphan*/  set_next (struct et_occ*,struct et_occ*) ; 
 int /*<<< orphan*/  set_prev (struct et_occ*,struct et_occ*) ; 

void
et_set_father (struct et_node *t, struct et_node *father)
{
  struct et_node *left, *right;
  struct et_occ *rmost, *left_part, *new_f_occ, *p;

  /* Update the path represented in the splay tree.  */
  new_f_occ = et_new_occ (father);

  rmost = father->rightmost_occ;
  et_splay (rmost);

  left_part = rmost->prev;

  p = t->rightmost_occ;
  et_splay (p);

  set_prev (new_f_occ, left_part);
  set_next (new_f_occ, p);

  p->depth++;
  p->min++;
  et_recomp_min (new_f_occ);

  set_prev (rmost, new_f_occ);

  if (new_f_occ->min + rmost->depth < rmost->min)
    {
      rmost->min = new_f_occ->min + rmost->depth;
      rmost->min_occ = new_f_occ->min_occ;
    }

  t->parent_occ = new_f_occ;

  /* Update the tree.  */
  t->father = father;
  right = father->son;
  if (right)
    left = right->left;
  else
    left = right = t;

  left->right = t;
  right->left = t;
  t->left = left;
  t->right = right;

  father->son = t;

#ifdef DEBUG_ET
  et_check_tree_sanity (rmost);
  record_path_before (rmost);
#endif
}