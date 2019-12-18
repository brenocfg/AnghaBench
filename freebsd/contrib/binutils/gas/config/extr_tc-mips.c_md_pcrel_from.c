#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  long valueT ;
struct TYPE_5__ {long fx_where; int fx_r_type; int /*<<< orphan*/  fx_line; int /*<<< orphan*/  fx_file; int /*<<< orphan*/  fx_addsy; TYPE_1__* fx_frag; } ;
typedef  TYPE_2__ fixS ;
struct TYPE_4__ {long fr_address; } ;

/* Variables and functions */
#define  BFD_RELOC_16_PCREL_S2 129 
#define  BFD_RELOC_MIPS_JMP 128 
 int /*<<< orphan*/  S_GET_SEGMENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_bad_where (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  now_seg ; 

long
md_pcrel_from (fixS *fixP)
{
  valueT addr = fixP->fx_where + fixP->fx_frag->fr_address;
  switch (fixP->fx_r_type)
    {
    case BFD_RELOC_16_PCREL_S2:
    case BFD_RELOC_MIPS_JMP:
      /* Return the address of the delay slot.  */
      return addr + 4;
    default:
      /* We have no relocation type for PC relative MIPS16 instructions.  */
      if (fixP->fx_addsy && S_GET_SEGMENT (fixP->fx_addsy) != now_seg)
	as_bad_where (fixP->fx_file, fixP->fx_line,
		      _("PC relative MIPS16 instruction references a different section"));
      return addr;
    }
}