#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * tree ;
struct edge_to_cases_elt {int /*<<< orphan*/ * case_labels; TYPE_1__* e; } ;
typedef  TYPE_1__* edge ;
typedef  int /*<<< orphan*/  basic_block ;
struct TYPE_3__ {int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int /*<<< orphan*/ * CASE_LABEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NO_INSERT ; 
 int /*<<< orphan*/ * SWITCH_LABELS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TREE_VEC_ELT (int /*<<< orphan*/ *,size_t) ; 
 size_t TREE_VEC_LENGTH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  edge_to_cases ; 
 int /*<<< orphan*/  find_edge (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void** htab_find_slot (int /*<<< orphan*/ ,struct edge_to_cases_elt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  label_to_block (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  record_switch_edge (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recording_case_labels_p () ; 

__attribute__((used)) static tree
get_cases_for_edge (edge e, tree t)
{
  struct edge_to_cases_elt elt, *elt_p;
  void **slot;
  size_t i, n;
  tree vec;

  /* If we are not recording cases, then we do not have CASE_LABEL_EXPR
     chains available.  Return NULL so the caller can detect this case.  */
  if (!recording_case_labels_p ())
    return NULL;

restart:
  elt.e = e;
  elt.case_labels = NULL;
  slot = htab_find_slot (edge_to_cases, &elt, NO_INSERT);

  if (slot)
    {
      elt_p = (struct edge_to_cases_elt *)*slot;
      return elt_p->case_labels;
    }

  /* If we did not find E in the hash table, then this must be the first
     time we have been queried for information about E & T.  Add all the
     elements from T to the hash table then perform the query again.  */

  vec = SWITCH_LABELS (t);
  n = TREE_VEC_LENGTH (vec);
  for (i = 0; i < n; i++)
    {
      tree lab = CASE_LABEL (TREE_VEC_ELT (vec, i));
      basic_block label_bb = label_to_block (lab);
      record_switch_edge (find_edge (e->src, label_bb), TREE_VEC_ELT (vec, i));
    }
  goto restart;
}