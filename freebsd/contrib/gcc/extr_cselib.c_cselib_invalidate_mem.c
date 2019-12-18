#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct elt_loc_list {struct elt_loc_list* next; int /*<<< orphan*/  loc; } ;
struct elt_list {struct elt_list* next; TYPE_1__* elt; } ;
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_5__ {scalar_t__ locs; struct TYPE_5__* next_containing_mem; struct elt_list* addr_list; } ;
typedef  TYPE_1__ cselib_val ;

/* Variables and functions */
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEM_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PARAM_MAX_CSELIB_MEMORY_LOCATIONS ; 
 int PARAM_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  canon_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  canon_true_dependence (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* cselib_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cselib_rtx_varies_p ; 
 TYPE_1__ dummy_val ; 
 TYPE_1__* first_containing_mem ; 
 int /*<<< orphan*/  get_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  n_useless_values ; 
 int /*<<< orphan*/  unchain_one_elt_list (struct elt_list**) ; 
 int /*<<< orphan*/  unchain_one_elt_loc_list (struct elt_loc_list**) ; 

__attribute__((used)) static void
cselib_invalidate_mem (rtx mem_rtx)
{
  cselib_val **vp, *v, *next;
  int num_mems = 0;
  rtx mem_addr;

  mem_addr = canon_rtx (get_addr (XEXP (mem_rtx, 0)));
  mem_rtx = canon_rtx (mem_rtx);

  vp = &first_containing_mem;
  for (v = *vp; v != &dummy_val; v = next)
    {
      bool has_mem = false;
      struct elt_loc_list **p = &v->locs;
      int had_locs = v->locs != 0;

      while (*p)
	{
	  rtx x = (*p)->loc;
	  cselib_val *addr;
	  struct elt_list **mem_chain;

	  /* MEMs may occur in locations only at the top level; below
	     that every MEM or REG is substituted by its VALUE.  */
	  if (!MEM_P (x))
	    {
	      p = &(*p)->next;
	      continue;
	    }
	  if (num_mems < PARAM_VALUE (PARAM_MAX_CSELIB_MEMORY_LOCATIONS)
	      && ! canon_true_dependence (mem_rtx, GET_MODE (mem_rtx), mem_addr,
		      			  x, cselib_rtx_varies_p))
	    {
	      has_mem = true;
	      num_mems++;
	      p = &(*p)->next;
	      continue;
	    }

	  /* This one overlaps.  */
	  /* We must have a mapping from this MEM's address to the
	     value (E).  Remove that, too.  */
	  addr = cselib_lookup (XEXP (x, 0), VOIDmode, 0);
	  mem_chain = &addr->addr_list;
	  for (;;)
	    {
	      if ((*mem_chain)->elt == v)
		{
		  unchain_one_elt_list (mem_chain);
		  break;
		}

	      mem_chain = &(*mem_chain)->next;
	    }

	  unchain_one_elt_loc_list (p);
	}

      if (had_locs && v->locs == 0)
	n_useless_values++;

      next = v->next_containing_mem;
      if (has_mem)
	{
	  *vp = v;
	  vp = &(*vp)->next_containing_mem;
	}
      else
	v->next_containing_mem = NULL;
    }
  *vp = &dummy_val;
}