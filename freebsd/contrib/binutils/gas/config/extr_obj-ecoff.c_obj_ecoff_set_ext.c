#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  symbolS ;
struct ecoff_debug_swap {int /*<<< orphan*/  (* swap_ext_out ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  external_ext_size; } ;
struct TYPE_4__ {int /*<<< orphan*/  native; int /*<<< orphan*/  local; } ;
typedef  TYPE_1__ ecoff_symbol_type ;
struct TYPE_5__ {struct ecoff_debug_swap debug_swap; } ;
typedef  int /*<<< orphan*/  EXTR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ bfd_asymbol_flavour (int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_target_ecoff_flavour ; 
 TYPE_3__* ecoff_backend (int /*<<< orphan*/ ) ; 
 TYPE_1__* ecoffsymbol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  know (int) ; 
 int /*<<< orphan*/  stdoutput ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  symbol_get_bfdsym (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmalloc (int /*<<< orphan*/ ) ; 

void
obj_ecoff_set_ext (symbolS *sym, EXTR *ext)
{
  const struct ecoff_debug_swap * const debug_swap
    = &ecoff_backend (stdoutput)->debug_swap;
  ecoff_symbol_type *esym;

  know (bfd_asymbol_flavour (symbol_get_bfdsym (sym))
	== bfd_target_ecoff_flavour);
  esym = ecoffsymbol (symbol_get_bfdsym (sym));
  esym->local = FALSE;
  esym->native = xmalloc (debug_swap->external_ext_size);
  (*debug_swap->swap_ext_out) (stdoutput, ext, esym->native);
}