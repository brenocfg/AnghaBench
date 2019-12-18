#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ segT ;
typedef  int offsetT ;
struct TYPE_6__ {int fx_where; int fx_r_type; int /*<<< orphan*/ * fx_addsy; scalar_t__ fx_pcrel; TYPE_1__* fx_frag; } ;
typedef  TYPE_2__ fixS ;
struct TYPE_5__ {int fr_address; } ;

/* Variables and functions */
#define  BFD_RELOC_ARM_CP_OFF_IMM 149 
#define  BFD_RELOC_ARM_HWLITERAL 148 
#define  BFD_RELOC_ARM_LITERAL 147 
#define  BFD_RELOC_ARM_OFFSET_IMM 146 
#define  BFD_RELOC_ARM_OFFSET_IMM8 145 
#define  BFD_RELOC_ARM_PCREL_BLX 144 
#define  BFD_RELOC_ARM_PCREL_BRANCH 143 
#define  BFD_RELOC_ARM_PCREL_CALL 142 
#define  BFD_RELOC_ARM_PCREL_JUMP 141 
#define  BFD_RELOC_ARM_PLT32 140 
#define  BFD_RELOC_ARM_T32_ADD_PC12 139 
#define  BFD_RELOC_ARM_T32_CP_OFF_IMM 138 
#define  BFD_RELOC_ARM_T32_OFFSET_IMM 137 
#define  BFD_RELOC_ARM_THUMB_ADD 136 
#define  BFD_RELOC_ARM_THUMB_OFFSET 135 
#define  BFD_RELOC_THUMB_PCREL_BLX 134 
#define  BFD_RELOC_THUMB_PCREL_BRANCH12 133 
#define  BFD_RELOC_THUMB_PCREL_BRANCH20 132 
#define  BFD_RELOC_THUMB_PCREL_BRANCH23 131 
#define  BFD_RELOC_THUMB_PCREL_BRANCH25 130 
#define  BFD_RELOC_THUMB_PCREL_BRANCH7 129 
#define  BFD_RELOC_THUMB_PCREL_BRANCH9 128 
 scalar_t__ S_GET_SEGMENT (int /*<<< orphan*/ *) ; 
 scalar_t__ S_IS_EXTERNAL (int /*<<< orphan*/ *) ; 
 scalar_t__ arm_force_relocation (TYPE_2__*) ; 

long
md_pcrel_from_section (fixS * fixP, segT seg)
{
  offsetT base = fixP->fx_where + fixP->fx_frag->fr_address;

  /* If this is pc-relative and we are going to emit a relocation
     then we just want to put out any pipeline compensation that the linker
     will need.  Otherwise we want to use the calculated base.
     For WinCE we skip the bias for externals as well, since this
     is how the MS ARM-CE assembler behaves and we want to be compatible.  */
  if (fixP->fx_pcrel 
      && ((fixP->fx_addsy && S_GET_SEGMENT (fixP->fx_addsy) != seg)
	  || (arm_force_relocation (fixP)
#ifdef TE_WINCE
	      && !S_IS_EXTERNAL (fixP->fx_addsy)
#endif
	      )))
    base = 0;

  switch (fixP->fx_r_type)
    {
      /* PC relative addressing on the Thumb is slightly odd as the
	 bottom two bits of the PC are forced to zero for the
	 calculation.  This happens *after* application of the
	 pipeline offset.  However, Thumb adrl already adjusts for
	 this, so we need not do it again.  */
    case BFD_RELOC_ARM_THUMB_ADD:
      return base & ~3;

    case BFD_RELOC_ARM_THUMB_OFFSET:
    case BFD_RELOC_ARM_T32_OFFSET_IMM:
    case BFD_RELOC_ARM_T32_ADD_PC12:
    case BFD_RELOC_ARM_T32_CP_OFF_IMM:
      return (base + 4) & ~3;

      /* Thumb branches are simply offset by +4.  */
    case BFD_RELOC_THUMB_PCREL_BRANCH7:
    case BFD_RELOC_THUMB_PCREL_BRANCH9:
    case BFD_RELOC_THUMB_PCREL_BRANCH12:
    case BFD_RELOC_THUMB_PCREL_BRANCH20:
    case BFD_RELOC_THUMB_PCREL_BRANCH23:
    case BFD_RELOC_THUMB_PCREL_BRANCH25:
    case BFD_RELOC_THUMB_PCREL_BLX:
      return base + 4;

      /* ARM mode branches are offset by +8.  However, the Windows CE
	 loader expects the relocation not to take this into account.  */
    case BFD_RELOC_ARM_PCREL_BRANCH:
    case BFD_RELOC_ARM_PCREL_CALL:
    case BFD_RELOC_ARM_PCREL_JUMP:
    case BFD_RELOC_ARM_PCREL_BLX:
    case BFD_RELOC_ARM_PLT32:
#ifdef TE_WINCE
      /* When handling fixups immediately, because we have already 
         discovered the value of a symbol, or the address of the frag involved
	 we must account for the offset by +8, as the OS loader will never see the reloc.
         see fixup_segment() in write.c
         The S_IS_EXTERNAL test handles the case of global symbols.
         Those need the calculated base, not just the pipe compensation the linker will need.  */
      if (fixP->fx_pcrel
	  && fixP->fx_addsy != NULL
	  && (S_GET_SEGMENT (fixP->fx_addsy) == seg)
	  && (S_IS_EXTERNAL (fixP->fx_addsy) || !arm_force_relocation (fixP)))
	return base + 8;
      return base;
#else
      return base + 8;
#endif

      /* ARM mode loads relative to PC are also offset by +8.  Unlike
	 branches, the Windows CE loader *does* expect the relocation
	 to take this into account.  */
    case BFD_RELOC_ARM_OFFSET_IMM:
    case BFD_RELOC_ARM_OFFSET_IMM8:
    case BFD_RELOC_ARM_HWLITERAL:
    case BFD_RELOC_ARM_LITERAL:
    case BFD_RELOC_ARM_CP_OFF_IMM:
      return base + 8;


      /* Other PC-relative relocations are un-offset.  */
    default:
      return base;
    }
}