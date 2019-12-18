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
typedef  int valueT ;
typedef  unsigned short value ;
typedef  scalar_t__ segT ;
typedef  int offsetT ;
struct TYPE_6__ {int fx_where; int fx_r_type; int fx_done; int fx_addnumber; int fx_offset; int fx_size; int /*<<< orphan*/  fx_line; int /*<<< orphan*/  fx_file; TYPE_1__* fx_frag; int /*<<< orphan*/ * fx_addsy; scalar_t__ fx_pcrel; } ;
typedef  TYPE_2__ fixS ;
struct TYPE_5__ {char* fr_literal; int /*<<< orphan*/  fr_opcode; } ;

/* Variables and functions */
#define  BFD_RELOC_16 146 
#define  BFD_RELOC_32 145 
#define  BFD_RELOC_8 144 
#define  BFD_RELOC_GPREL32 143 
#define  BFD_RELOC_HI16_S 142 
#define  BFD_RELOC_LO16 141 
#define  BFD_RELOC_NONE 140 
#define  BFD_RELOC_RVA 139 
#define  BFD_RELOC_SCORE16_BRANCH 138 
#define  BFD_RELOC_SCORE16_JMP 137 
#define  BFD_RELOC_SCORE_BRANCH 136 
#define  BFD_RELOC_SCORE_CALL15 135 
#define  BFD_RELOC_SCORE_DUMMY_HI16 134 
#define  BFD_RELOC_SCORE_GOT15 133 
#define  BFD_RELOC_SCORE_GOT_LO16 132 
#define  BFD_RELOC_SCORE_GPREL15 131 
#define  BFD_RELOC_SCORE_JMP 130 
 int BFD_RELOC_UNUSED ; 
#define  BFD_RELOC_VTABLE_ENTRY 129 
#define  BFD_RELOC_VTABLE_INHERIT 128 
 int INSN16_SIZE ; 
 int INSN_SIZE ; 
 scalar_t__ S_GET_SEGMENT (int /*<<< orphan*/ *) ; 
 scalar_t__ S_IS_DEFINED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_IS_EXTERNAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_IS_WEAK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_SET_WEAK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_bad_where (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int md_chars_to_number (char*,int) ; 
 int /*<<< orphan*/  md_number_to_chars (char*,int,int) ; 
 scalar_t__ md_pcrel_from (TYPE_2__*) ; 

void
md_apply_fix (fixS *fixP, valueT *valP, segT seg)
{
  offsetT value = *valP;
  offsetT abs_value = 0;
  offsetT newval;
  offsetT content;
  unsigned short HI, LO;

  char *buf = fixP->fx_frag->fr_literal + fixP->fx_where;

  assert (fixP->fx_r_type < BFD_RELOC_UNUSED);
  if (fixP->fx_addsy == 0 && !fixP->fx_pcrel)
    {
      if (fixP->fx_r_type != BFD_RELOC_SCORE_DUMMY_HI16)
        fixP->fx_done = 1;
    }

  /* If this symbol is in a different section then we need to leave it for
     the linker to deal with.  Unfortunately, md_pcrel_from can't tell,
     so we have to undo it's effects here.  */
  if (fixP->fx_pcrel)
    {
      if (fixP->fx_addsy != NULL
	  && S_IS_DEFINED (fixP->fx_addsy)
	  && S_GET_SEGMENT (fixP->fx_addsy) != seg)
	value += md_pcrel_from (fixP);
    }

  /* Remember value for emit_reloc.  */
  fixP->fx_addnumber = value;

  switch (fixP->fx_r_type)
    {
    case BFD_RELOC_HI16_S:
      if (fixP->fx_done)
        {                       /* For la rd, imm32.  */
          newval = md_chars_to_number (buf, INSN_SIZE);
          HI = (value) >> 16;   /* mul to 2, then take the hi 16 bit.  */
          newval |= (HI & 0x3fff) << 1;
          newval |= ((HI >> 14) & 0x3) << 16;
          md_number_to_chars (buf, newval, INSN_SIZE);
        }
      break;
    case BFD_RELOC_LO16:
      if (fixP->fx_done)        /* For la rd, imm32.  */
        {
          newval = md_chars_to_number (buf, INSN_SIZE);
          LO = (value) & 0xffff;
          newval |= (LO & 0x3fff) << 1; /* 16 bit: imm -> 14 bit in lo, 2 bit in hi.  */
          newval |= ((LO >> 14) & 0x3) << 16;
          md_number_to_chars (buf, newval, INSN_SIZE);
        }
      break;
    case BFD_RELOC_SCORE_JMP:
      {
        content = md_chars_to_number (buf, INSN_SIZE);
        value = fixP->fx_offset;
        content = (content & ~0x3ff7ffe) | ((value << 1) & 0x3ff0000) | (value & 0x7fff);
        md_number_to_chars (buf, content, INSN_SIZE);
      }
      break;
    case BFD_RELOC_SCORE_BRANCH:
      if ((S_GET_SEGMENT (fixP->fx_addsy) != seg) || (fixP->fx_addsy != NULL && S_IS_EXTERNAL (fixP->fx_addsy)))
        value = fixP->fx_offset;
      else
        fixP->fx_done = 1;

      content = md_chars_to_number (buf, INSN_SIZE);
      if ((fixP->fx_frag->fr_opcode != 0) && ((content & 0x80008000) != 0x80008000))
        {
          if ((value & 0x80000000) == 0x80000000)
            abs_value = 0xffffffff - value + 1;
          if ((abs_value & 0xffffff00) != 0)
            {
              as_bad_where (fixP->fx_file, fixP->fx_line,
                            _(" branch relocation truncate (0x%x) [-2^8 ~ 2^8]"), (unsigned int)value);
              return;
            }
          content = md_chars_to_number (buf, INSN16_SIZE);
          content &= 0xff00;
          content = (content & 0xff00) | ((value >> 1) & 0xff);
          md_number_to_chars (buf, content, INSN16_SIZE);
          fixP->fx_r_type = BFD_RELOC_SCORE16_BRANCH;
          fixP->fx_size = 2;
        }
      else
        {
          if ((value & 0x80000000) == 0x80000000)
            abs_value = 0xffffffff - value + 1;
          if ((abs_value & 0xfff80000) != 0)
            {
              as_bad_where (fixP->fx_file, fixP->fx_line,
                            _(" branch relocation truncate (0x%x) [-2^19 ~ 2^19]"), (unsigned int)value);
              return;
            }
          content = md_chars_to_number (buf, INSN_SIZE);
          content &= 0xfc00fc01;
          content = (content & 0xfc00fc01) | (value & 0x3fe) | ((value << 6) & 0x3ff0000);
          md_number_to_chars (buf, content, INSN_SIZE);
        }
      break;
    case BFD_RELOC_SCORE16_JMP:
      content = md_chars_to_number (buf, INSN16_SIZE);
      content &= 0xf001;
      value = fixP->fx_offset & 0xfff;
      content = (content & 0xfc01) | (value & 0xffe);
      md_number_to_chars (buf, content, INSN16_SIZE);
      break;
    case BFD_RELOC_SCORE16_BRANCH:
      content = md_chars_to_number (buf, INSN_SIZE);
      if ((fixP->fx_frag->fr_opcode != 0) && ((content & 0x80008000) == 0x80008000))
        {
          if ((S_GET_SEGMENT (fixP->fx_addsy) != seg) ||
              (fixP->fx_addsy != NULL && S_IS_EXTERNAL (fixP->fx_addsy)))
            value = fixP->fx_offset;
          else
            fixP->fx_done = 1;
          if ((value & 0x80000000) == 0x80000000)
            abs_value = 0xffffffff - value + 1;
          if ((abs_value & 0xfff80000) != 0)
            {
              as_bad_where (fixP->fx_file, fixP->fx_line,
                            _(" branch relocation truncate (0x%x) [-2^19 ~ 2^19]"), (unsigned int)value);
              return;
            }
          content = md_chars_to_number (buf, INSN_SIZE);
          content = (content & 0xfc00fc01) | (value & 0x3fe) | ((value << 6) & 0x3ff0000);
          md_number_to_chars (buf, content, INSN_SIZE);
          fixP->fx_r_type = BFD_RELOC_SCORE_BRANCH;
          fixP->fx_size = 4;
          break;
        }
      else
        {
          /* In differnt section.  */
          if ((S_GET_SEGMENT (fixP->fx_addsy) != seg) ||
              (fixP->fx_addsy != NULL && S_IS_EXTERNAL (fixP->fx_addsy)))
            value = fixP->fx_offset;
          else
            fixP->fx_done = 1;

          if ((value & 0x80000000) == 0x80000000)
            abs_value = 0xffffffff - value + 1;
          if ((abs_value & 0xffffff00) != 0)
            {
              as_bad_where (fixP->fx_file, fixP->fx_line,
                            _(" branch relocation truncate (0x%x)  [-2^8 ~ 2^8]"), (unsigned int)value);
              return;
            }
          content = md_chars_to_number (buf, INSN16_SIZE);
          content = (content & 0xff00) | ((value >> 1) & 0xff);
          md_number_to_chars (buf, content, INSN16_SIZE);
          break;
        }
    case BFD_RELOC_8:
      if (fixP->fx_done || fixP->fx_pcrel)
	md_number_to_chars (buf, value, 1);
#ifdef OBJ_ELF
      else
        {
          value = fixP->fx_offset;
          md_number_to_chars (buf, value, 1);
        }
#endif
      break;

    case BFD_RELOC_16:
      if (fixP->fx_done || fixP->fx_pcrel)
        md_number_to_chars (buf, value, 2);
#ifdef OBJ_ELF
      else
        {
          value = fixP->fx_offset;
          md_number_to_chars (buf, value, 2);
        }
#endif
      break;
    case BFD_RELOC_RVA:
    case BFD_RELOC_32:
      if (fixP->fx_done || fixP->fx_pcrel)
        md_number_to_chars (buf, value, 4);
#ifdef OBJ_ELF
      else
        {
          value = fixP->fx_offset;
          md_number_to_chars (buf, value, 4);
        }
#endif
      break;
    case BFD_RELOC_VTABLE_INHERIT:
      fixP->fx_done = 0;
      if (fixP->fx_addsy && !S_IS_DEFINED (fixP->fx_addsy) && !S_IS_WEAK (fixP->fx_addsy))
        S_SET_WEAK (fixP->fx_addsy);
      break;
    case BFD_RELOC_VTABLE_ENTRY:
      fixP->fx_done = 0;
      break;
    case BFD_RELOC_SCORE_GPREL15:
      content = md_chars_to_number (buf, INSN_SIZE);
      if ((fixP->fx_frag->fr_opcode != 0) && ((content & 0xfc1c8000) != 0x94188000))
        fixP->fx_r_type = BFD_RELOC_NONE;
      fixP->fx_done = 0;
      break;
    case BFD_RELOC_SCORE_GOT15:
    case BFD_RELOC_SCORE_DUMMY_HI16:
    case BFD_RELOC_SCORE_GOT_LO16:
    case BFD_RELOC_SCORE_CALL15:
    case BFD_RELOC_GPREL32:
      break;
    case BFD_RELOC_NONE:
    default:
      as_bad_where (fixP->fx_file, fixP->fx_line, _("bad relocation fixup type (%d)"), fixP->fx_r_type);
    }
}