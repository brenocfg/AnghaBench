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
typedef  int offsetT ;
struct TYPE_4__ {int fr_offset; int /*<<< orphan*/  fr_subtype; scalar_t__ fr_fix; scalar_t__ fr_address; int /*<<< orphan*/  fr_symbol; } ;
typedef  TYPE_1__ fragS ;
typedef  scalar_t__ bfd_boolean ;
typedef  int /*<<< orphan*/  asection ;
typedef  scalar_t__ addressT ;
struct TYPE_5__ {scalar_t__ isa; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ ISA_MIPS1 ; 
 scalar_t__ NO_PIC ; 
 int /*<<< orphan*/  RELAX_BRANCH_ENCODE (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int RELAX_BRANCH_LIKELY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RELAX_BRANCH_LINK (int /*<<< orphan*/ ) ; 
 scalar_t__ RELAX_BRANCH_TOOFAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RELAX_BRANCH_UNCOND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * S_GET_SEGMENT (int /*<<< orphan*/ ) ; 
 int S_GET_VALUE (int /*<<< orphan*/ ) ; 
 scalar_t__ S_IS_DEFINED (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 TYPE_3__ mips_opts ; 
 scalar_t__ mips_pic ; 

__attribute__((used)) static int
relaxed_branch_length (fragS *fragp, asection *sec, int update)
{
  bfd_boolean toofar;
  int length;

  if (fragp
      && S_IS_DEFINED (fragp->fr_symbol)
      && sec == S_GET_SEGMENT (fragp->fr_symbol))
    {
      addressT addr;
      offsetT val;

      val = S_GET_VALUE (fragp->fr_symbol) + fragp->fr_offset;

      addr = fragp->fr_address + fragp->fr_fix + 4;

      val -= addr;

      toofar = val < - (0x8000 << 2) || val >= (0x8000 << 2);
    }
  else if (fragp)
    /* If the symbol is not defined or it's in a different segment,
       assume the user knows what's going on and emit a short
       branch.  */
    toofar = FALSE;
  else
    toofar = TRUE;

  if (fragp && update && toofar != RELAX_BRANCH_TOOFAR (fragp->fr_subtype))
    fragp->fr_subtype
      = RELAX_BRANCH_ENCODE (RELAX_BRANCH_UNCOND (fragp->fr_subtype),
			     RELAX_BRANCH_LIKELY (fragp->fr_subtype),
			     RELAX_BRANCH_LINK (fragp->fr_subtype),
			     toofar);

  length = 4;
  if (toofar)
    {
      if (fragp ? RELAX_BRANCH_LIKELY (fragp->fr_subtype) : (update > 0))
	length += 8;

      if (mips_pic != NO_PIC)
	{
	  /* Additional space for PIC loading of target address.  */
	  length += 8;
	  if (mips_opts.isa == ISA_MIPS1)
	    /* Additional space for $at-stabilizing nop.  */
	    length += 4;
	}

      /* If branch is conditional.  */
      if (fragp ? !RELAX_BRANCH_UNCOND (fragp->fr_subtype) : (update >= 0))
	length += 8;
    }

  return length;
}