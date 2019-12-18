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
struct TYPE_4__ {scalar_t__ fx_r_type; int /*<<< orphan*/ * fx_addsy; int /*<<< orphan*/ * fx_subsy; } ;
typedef  TYPE_1__ fixS ;
struct TYPE_5__ {int flags; } ;

/* Variables and functions */
 scalar_t__ BFD_RELOC_LO16 ; 
 scalar_t__ BFD_RELOC_MIPS16_LO16 ; 
 scalar_t__ BFD_RELOC_VTABLE_ENTRY ; 
 scalar_t__ BFD_RELOC_VTABLE_INHERIT ; 
 scalar_t__ HAVE_IN_PLACE_ADDENDS ; 
 scalar_t__ IS_ELF ; 
 int SEC_MERGE ; 
 scalar_t__ STO_MIPS16 ; 
 scalar_t__ S_GET_OTHER (int /*<<< orphan*/ *) ; 
 TYPE_3__* S_GET_SEGMENT (int /*<<< orphan*/ *) ; 
 scalar_t__ reloc_needs_lo_p (scalar_t__) ; 
 scalar_t__* symbol_get_tc (int /*<<< orphan*/ *) ; 

int
mips_fix_adjustable (fixS *fixp)
{
  if (fixp->fx_r_type == BFD_RELOC_VTABLE_INHERIT
      || fixp->fx_r_type == BFD_RELOC_VTABLE_ENTRY)
    return 0;

  if (fixp->fx_addsy == NULL)
    return 1;

  /* If symbol SYM is in a mergeable section, relocations of the form
     SYM + 0 can usually be made section-relative.  The mergeable data
     is then identified by the section offset rather than by the symbol.

     However, if we're generating REL LO16 relocations, the offset is split
     between the LO16 and parterning high part relocation.  The linker will
     need to recalculate the complete offset in order to correctly identify
     the merge data.

     The linker has traditionally not looked for the parterning high part
     relocation, and has thus allowed orphaned R_MIPS_LO16 relocations to be
     placed anywhere.  Rather than break backwards compatibility by changing
     this, it seems better not to force the issue, and instead keep the
     original symbol.  This will work with either linker behavior.  */
  if ((fixp->fx_r_type == BFD_RELOC_LO16
       || fixp->fx_r_type == BFD_RELOC_MIPS16_LO16
       || reloc_needs_lo_p (fixp->fx_r_type))
      && HAVE_IN_PLACE_ADDENDS
      && (S_GET_SEGMENT (fixp->fx_addsy)->flags & SEC_MERGE) != 0)
    return 0;

#ifdef OBJ_ELF
  /* R_MIPS16_26 relocations against non-MIPS16 functions might resolve
     to a floating-point stub.  The same is true for non-R_MIPS16_26
     relocations against MIPS16 functions; in this case, the stub becomes
     the function's canonical address.

     Floating-point stubs are stored in unique .mips16.call.* or
     .mips16.fn.* sections.  If a stub T for function F is in section S,
     the first relocation in section S must be against F; this is how the
     linker determines the target function.  All relocations that might
     resolve to T must also be against F.  We therefore have the following
     restrictions, which are given in an intentionally-redundant way:

       1. We cannot reduce R_MIPS16_26 relocations against non-MIPS16
	  symbols.

       2. We cannot reduce a stub's relocations against non-MIPS16 symbols
	  if that stub might be used.

       3. We cannot reduce non-R_MIPS16_26 relocations against MIPS16
	  symbols.

       4. We cannot reduce a stub's relocations against MIPS16 symbols if
	  that stub might be used.

     There is a further restriction:

       5. We cannot reduce R_MIPS16_26 relocations against MIPS16 symbols
	  on targets with in-place addends; the relocation field cannot
	  encode the low bit.

     For simplicity, we deal with (3)-(5) by not reducing _any_ relocation
     against a MIPS16 symbol.

     We deal with (1)-(2) by saying that, if there's a R_MIPS16_26
     relocation against some symbol R, no relocation against R may be
     reduced.  (Note that this deals with (2) as well as (1) because
     relocations against global symbols will never be reduced on ELF
     targets.)  This approach is a little simpler than trying to detect
     stub sections, and gives the "all or nothing" per-symbol consistency
     that we have for MIPS16 symbols.  */
  if (IS_ELF
      && fixp->fx_subsy == NULL
      && (S_GET_OTHER (fixp->fx_addsy) == STO_MIPS16
	  || *symbol_get_tc (fixp->fx_addsy)))
    return 0;
#endif

  return 1;
}