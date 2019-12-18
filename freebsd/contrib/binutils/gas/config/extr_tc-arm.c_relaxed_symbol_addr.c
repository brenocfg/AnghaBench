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
typedef  int /*<<< orphan*/  symbolS ;
struct TYPE_5__ {scalar_t__ relax_marker; scalar_t__ fr_offset; int /*<<< orphan*/ * fr_symbol; } ;
typedef  TYPE_1__ fragS ;
typedef  scalar_t__ addressT ;

/* Variables and functions */
 scalar_t__ S_GET_SEGMENT (int /*<<< orphan*/ *) ; 
 scalar_t__ S_GET_VALUE (int /*<<< orphan*/ *) ; 
 scalar_t__ absolute_section ; 
 int /*<<< orphan*/  know (int) ; 
 TYPE_1__* symbol_get_frag (int /*<<< orphan*/ *) ; 
 TYPE_1__ zero_address_frag ; 

__attribute__((used)) static addressT
relaxed_symbol_addr(fragS *fragp, long stretch)
{
  fragS *sym_frag;
  addressT addr;
  symbolS *sym;

  sym = fragp->fr_symbol;
  sym_frag = symbol_get_frag (sym);
  know (S_GET_SEGMENT (sym) != absolute_section
	|| sym_frag == &zero_address_frag);
  addr = S_GET_VALUE (sym) + fragp->fr_offset;

  /* If frag has yet to be reached on this pass, assume it will
     move by STRETCH just as we did.  If this is not so, it will
     be because some frag between grows, and that will force
     another pass.  */

  if (stretch != 0
      && sym_frag->relax_marker != fragp->relax_marker)
    addr += stretch;

  return addr;
}