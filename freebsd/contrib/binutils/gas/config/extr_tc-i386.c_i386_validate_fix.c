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
struct TYPE_3__ {scalar_t__ fx_subsy; scalar_t__ fx_r_type; } ;
typedef  TYPE_1__ fixS ;

/* Variables and functions */
 scalar_t__ BFD_RELOC_32_PCREL ; 
 scalar_t__ BFD_RELOC_386_GOTOFF ; 
 scalar_t__ BFD_RELOC_X86_64_GOTOFF64 ; 
 scalar_t__ BFD_RELOC_X86_64_GOTPCREL ; 
 scalar_t__ GOT_symbol ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  object_64bit ; 

void
i386_validate_fix (fixS *fixp)
{
  if (fixp->fx_subsy && fixp->fx_subsy == GOT_symbol)
    {
      if (fixp->fx_r_type == BFD_RELOC_32_PCREL)
	{
	  if (!object_64bit)
	    abort ();
	  fixp->fx_r_type = BFD_RELOC_X86_64_GOTPCREL;
	}
      else
	{
	  if (!object_64bit)
	    fixp->fx_r_type = BFD_RELOC_386_GOTOFF;
	  else
	    fixp->fx_r_type = BFD_RELOC_X86_64_GOTOFF64;
	}
      fixp->fx_subsy = 0;
    }
}