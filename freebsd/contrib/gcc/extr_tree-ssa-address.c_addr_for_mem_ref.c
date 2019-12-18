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
struct mem_address {scalar_t__ index; scalar_t__ base; scalar_t__ symbol; scalar_t__ offset; scalar_t__ step; } ;
struct mem_addr_template {void* ref; void** off_p; void** step_p; } ;
typedef  void* rtx ;

/* Variables and functions */
 int /*<<< orphan*/  EXPAND_NORMAL ; 
 scalar_t__ LAST_VIRTUAL_REGISTER ; 
 void* NULL_RTX ; 
 int /*<<< orphan*/  Pmode ; 
 int TEMPL_IDX (scalar_t__,scalar_t__,scalar_t__,void*,void*) ; 
 int /*<<< orphan*/  TREE_INT_CST_HIGH (scalar_t__) ; 
 int /*<<< orphan*/  TREE_INT_CST_LOW (scalar_t__) ; 
 scalar_t__ build_addr (scalar_t__,int /*<<< orphan*/ ) ; 
 void* const0_rtx ; 
 int /*<<< orphan*/  current_function_decl ; 
 void* expand_expr (scalar_t__,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_addr_rtx (void*,void*,void*,void*,void*,void**,void***,void***) ; 
 void* gen_raw_REG (int /*<<< orphan*/ ,scalar_t__) ; 
 void* gen_rtx_SYMBOL_REF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ggc_strdup (char*) ; 
 void* immed_double_const (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  integer_onep (scalar_t__) ; 
 int /*<<< orphan*/  integer_zerop (scalar_t__) ; 
 struct mem_addr_template* templates ; 

rtx
addr_for_mem_ref (struct mem_address *addr, bool really_expand)
{
  rtx address, sym, bse, idx, st, off;
  static bool templates_initialized = false;
  struct mem_addr_template *templ;

  if (addr->step && !integer_onep (addr->step))
    st = immed_double_const (TREE_INT_CST_LOW (addr->step),
			     TREE_INT_CST_HIGH (addr->step), Pmode);
  else
    st = NULL_RTX;

  if (addr->offset && !integer_zerop (addr->offset))
    off = immed_double_const (TREE_INT_CST_LOW (addr->offset),
			      TREE_INT_CST_HIGH (addr->offset), Pmode);
  else
    off = NULL_RTX;

  if (!really_expand)
    {
      /* Reuse the templates for addresses, so that we do not waste memory.  */
      if (!templates_initialized)
	{
	  unsigned i;

	  templates_initialized = true;
	  sym = gen_rtx_SYMBOL_REF (Pmode, ggc_strdup ("test_symbol"));
	  bse = gen_raw_REG (Pmode, LAST_VIRTUAL_REGISTER + 1);
	  idx = gen_raw_REG (Pmode, LAST_VIRTUAL_REGISTER + 2);

	  for (i = 0; i < 32; i++)
	    gen_addr_rtx ((i & 16 ? sym : NULL_RTX),
			  (i & 8 ? bse : NULL_RTX),
			  (i & 4 ? idx : NULL_RTX),
			  (i & 2 ? const0_rtx : NULL_RTX),
			  (i & 1 ? const0_rtx : NULL_RTX),
			  &templates[i].ref,
			  &templates[i].step_p,
			  &templates[i].off_p);
	}

      templ = templates + TEMPL_IDX (addr->symbol, addr->base, addr->index,
				     st, off);
      if (st)
	*templ->step_p = st;
      if (off)
	*templ->off_p = off;

      return templ->ref;
    }

  /* Otherwise really expand the expressions.  */
  sym = (addr->symbol
	 ? expand_expr (build_addr (addr->symbol, current_function_decl),
			NULL_RTX, Pmode, EXPAND_NORMAL)
	 : NULL_RTX);
  bse = (addr->base
	 ? expand_expr (addr->base, NULL_RTX, Pmode, EXPAND_NORMAL)
	 : NULL_RTX);
  idx = (addr->index
	 ? expand_expr (addr->index, NULL_RTX, Pmode, EXPAND_NORMAL)
	 : NULL_RTX);

  gen_addr_rtx (sym, bse, idx, st, off, &address, NULL, NULL);
  return address;
}