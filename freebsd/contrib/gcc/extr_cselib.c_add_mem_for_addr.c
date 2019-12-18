#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct elt_loc_list {int /*<<< orphan*/  loc; struct elt_loc_list* next; } ;
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_8__ {int /*<<< orphan*/  val_rtx; } ;
struct TYPE_9__ {struct TYPE_9__* next_containing_mem; TYPE_1__ u; struct elt_loc_list* locs; int /*<<< orphan*/  addr_list; } ;
typedef  TYPE_2__ cselib_val ;

/* Variables and functions */
 TYPE_2__* CSELIB_VAL_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* first_containing_mem ; 
 int /*<<< orphan*/  new_elt_list (int /*<<< orphan*/ ,TYPE_2__*) ; 
 struct elt_loc_list* new_elt_loc_list (struct elt_loc_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  replace_equiv_address_nv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
add_mem_for_addr (cselib_val *addr_elt, cselib_val *mem_elt, rtx x)
{
  struct elt_loc_list *l;

  /* Avoid duplicates.  */
  for (l = mem_elt->locs; l; l = l->next)
    if (MEM_P (l->loc)
	&& CSELIB_VAL_PTR (XEXP (l->loc, 0)) == addr_elt)
      return;

  addr_elt->addr_list = new_elt_list (addr_elt->addr_list, mem_elt);
  mem_elt->locs
    = new_elt_loc_list (mem_elt->locs,
			replace_equiv_address_nv (x, addr_elt->u.val_rtx));
  if (mem_elt->next_containing_mem == NULL)
    {
      mem_elt->next_containing_mem = first_containing_mem;
      first_containing_mem = mem_elt;
    }
}