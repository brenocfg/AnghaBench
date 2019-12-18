#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct occurrence {struct occurrence* next; struct occurrence* children; TYPE_1__* bb; } ;
typedef  TYPE_1__* basic_block ;
struct TYPE_7__ {int /*<<< orphan*/  aux; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDI_DOMINATORS ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 TYPE_1__* nearest_common_dominator (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 
 struct occurrence* occ_new (TYPE_1__*,struct occurrence*) ; 

__attribute__((used)) static void
insert_bb (struct occurrence *new_occ, basic_block idom,
	   struct occurrence **p_head)
{
  struct occurrence *occ, **p_occ;

  for (p_occ = p_head; (occ = *p_occ) != NULL; )
    {
      basic_block bb = new_occ->bb, occ_bb = occ->bb;
      basic_block dom = nearest_common_dominator (CDI_DOMINATORS, occ_bb, bb);
      if (dom == bb)
	{
	  /* BB dominates OCC_BB.  OCC becomes NEW_OCC's child: remove OCC
	     from its list.  */
	  *p_occ = occ->next;
	  occ->next = new_occ->children;
	  new_occ->children = occ;

	  /* Try the next block (it may as well be dominated by BB).  */
	}

      else if (dom == occ_bb)
	{
	  /* OCC_BB dominates BB.  Tail recurse to look deeper.  */
	  insert_bb (new_occ, dom, &occ->children);
	  return;
	}

      else if (dom != idom)
	{
	  gcc_assert (!dom->aux);

	  /* There is a dominator between IDOM and BB, add it and make
	     two children out of NEW_OCC and OCC.  First, remove OCC from
	     its list.	*/
	  *p_occ = occ->next;
	  new_occ->next = occ;
	  occ->next = NULL;

	  /* None of the previous blocks has DOM as a dominator: if we tail
	     recursed, we would reexamine them uselessly. Just switch BB with
	     DOM, and go on looking for blocks dominated by DOM.  */
          new_occ = occ_new (dom, new_occ);
	}

      else
	{
	  /* Nothing special, go on with the next element.  */
	  p_occ = &occ->next;
	}
    }

  /* No place was found as a child of IDOM.  Make BB a sibling of IDOM.  */
  new_occ->next = *p_head;
  *p_head = new_occ;
}