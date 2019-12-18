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
typedef  int valueT ;
struct alpha_operand {int dummy; } ;
typedef  int /*<<< orphan*/  segT ;
typedef  int /*<<< orphan*/  offsetT ;
struct TYPE_5__ {int fx_where; int fx_r_type; int fx_offset; int fx_done; scalar_t__ fx_addsy; scalar_t__ fx_pcrel; int /*<<< orphan*/  fx_line; int /*<<< orphan*/  fx_file; int /*<<< orphan*/  fx_subsy; TYPE_1__* fx_frag; struct TYPE_5__* fx_next; } ;
typedef  TYPE_2__ fixS ;
struct TYPE_4__ {char* fr_literal; int fr_address; } ;

/* Variables and functions */
#define  BFD_RELOC_16 156 
 int BFD_RELOC_16_PCREL ; 
#define  BFD_RELOC_23_PCREL_S2 155 
#define  BFD_RELOC_32 154 
 int BFD_RELOC_32_PCREL ; 
#define  BFD_RELOC_64 153 
 int BFD_RELOC_64_PCREL ; 
#define  BFD_RELOC_ALPHA_BRSGP 152 
#define  BFD_RELOC_ALPHA_CODEADDR 151 
#define  BFD_RELOC_ALPHA_DTPREL16 150 
#define  BFD_RELOC_ALPHA_DTPREL_HI16 149 
#define  BFD_RELOC_ALPHA_DTPREL_LO16 148 
#define  BFD_RELOC_ALPHA_ELF_LITERAL 147 
#define  BFD_RELOC_ALPHA_GOTDTPREL16 146 
#define  BFD_RELOC_ALPHA_GOTTPREL16 145 
 int BFD_RELOC_ALPHA_GPDISP ; 
#define  BFD_RELOC_ALPHA_GPDISP_HI16 144 
#define  BFD_RELOC_ALPHA_GPDISP_LO16 143 
#define  BFD_RELOC_ALPHA_GPREL_HI16 142 
#define  BFD_RELOC_ALPHA_GPREL_LO16 141 
#define  BFD_RELOC_ALPHA_HINT 140 
#define  BFD_RELOC_ALPHA_LINKAGE 139 
#define  BFD_RELOC_ALPHA_LITERAL 138 
#define  BFD_RELOC_ALPHA_LITUSE 137 
#define  BFD_RELOC_ALPHA_TLSGD 136 
#define  BFD_RELOC_ALPHA_TLSLDM 135 
#define  BFD_RELOC_ALPHA_TPREL16 134 
#define  BFD_RELOC_ALPHA_TPREL_HI16 133 
#define  BFD_RELOC_ALPHA_TPREL_LO16 132 
#define  BFD_RELOC_GPREL16 131 
#define  BFD_RELOC_GPREL32 130 
#define  BFD_RELOC_VTABLE_ENTRY 129 
#define  BFD_RELOC_VTABLE_INHERIT 128 
 int /*<<< orphan*/  S_GET_SEGMENT (scalar_t__) ; 
 int /*<<< orphan*/  S_SET_THREAD_LOCAL (scalar_t__) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  absolute_section ; 
 int /*<<< orphan*/  alpha_gp_symbol ; 
 unsigned int alpha_gp_value ; 
 scalar_t__ alpha_num_operands ; 
 struct alpha_operand* alpha_operands ; 
 int /*<<< orphan*/  as_bad_where (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  as_fatal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  as_warn_where (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bfd_get_reloc_code_name (int) ; 
 unsigned int bfd_getl32 (char* const) ; 
 unsigned int insert_operand (unsigned int,struct alpha_operand const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_number_to_chars (char* const,unsigned int,int) ; 
 scalar_t__ section_symbol (int /*<<< orphan*/ ) ; 
 int sign_extend_16 (int) ; 

void
md_apply_fix (fixS *fixP, valueT * valP, segT seg)
{
  char * const fixpos = fixP->fx_frag->fr_literal + fixP->fx_where;
  valueT value = * valP;
  unsigned image, size;

  switch (fixP->fx_r_type)
    {
      /* The GPDISP relocations are processed internally with a symbol
	 referring to the current function's section;  we need to drop
	 in a value which, when added to the address of the start of
	 the function, gives the desired GP.  */
    case BFD_RELOC_ALPHA_GPDISP_HI16:
      {
	fixS *next = fixP->fx_next;

	/* With user-specified !gpdisp relocations, we can be missing
	   the matching LO16 reloc.  We will have already issued an
	   error message.  */
	if (next)
	  fixP->fx_offset = (next->fx_frag->fr_address + next->fx_where
			     - fixP->fx_frag->fr_address - fixP->fx_where);

	value = (value - sign_extend_16 (value)) >> 16;
      }
#ifdef OBJ_ELF
      fixP->fx_r_type = BFD_RELOC_ALPHA_GPDISP;
#endif
      goto do_reloc_gp;

    case BFD_RELOC_ALPHA_GPDISP_LO16:
      value = sign_extend_16 (value);
      fixP->fx_offset = 0;
#ifdef OBJ_ELF
      fixP->fx_done = 1;
#endif

    do_reloc_gp:
      fixP->fx_addsy = section_symbol (seg);
      md_number_to_chars (fixpos, value, 2);
      break;

    case BFD_RELOC_16:
      if (fixP->fx_pcrel)
	fixP->fx_r_type = BFD_RELOC_16_PCREL;
      size = 2;
      goto do_reloc_xx;

    case BFD_RELOC_32:
      if (fixP->fx_pcrel)
	fixP->fx_r_type = BFD_RELOC_32_PCREL;
      size = 4;
      goto do_reloc_xx;

    case BFD_RELOC_64:
      if (fixP->fx_pcrel)
	fixP->fx_r_type = BFD_RELOC_64_PCREL;
      size = 8;

    do_reloc_xx:
      if (fixP->fx_pcrel == 0 && fixP->fx_addsy == 0)
	{
	  md_number_to_chars (fixpos, value, size);
	  goto done;
	}
      return;

#ifdef OBJ_ECOFF
    case BFD_RELOC_GPREL32:
      assert (fixP->fx_subsy == alpha_gp_symbol);
      fixP->fx_subsy = 0;
      /* FIXME: inherited this obliviousness of `value' -- why?  */
      md_number_to_chars (fixpos, -alpha_gp_value, 4);
      break;
#else
    case BFD_RELOC_GPREL32:
#endif
    case BFD_RELOC_GPREL16:
    case BFD_RELOC_ALPHA_GPREL_HI16:
    case BFD_RELOC_ALPHA_GPREL_LO16:
      return;

    case BFD_RELOC_23_PCREL_S2:
      if (fixP->fx_pcrel == 0 && fixP->fx_addsy == 0)
	{
	  image = bfd_getl32 (fixpos);
	  image = (image & ~0x1FFFFF) | ((value >> 2) & 0x1FFFFF);
	  goto write_done;
	}
      return;

    case BFD_RELOC_ALPHA_HINT:
      if (fixP->fx_pcrel == 0 && fixP->fx_addsy == 0)
	{
	  image = bfd_getl32 (fixpos);
	  image = (image & ~0x3FFF) | ((value >> 2) & 0x3FFF);
	  goto write_done;
	}
      return;

#ifdef OBJ_ELF
    case BFD_RELOC_ALPHA_BRSGP:
      return;

    case BFD_RELOC_ALPHA_TLSGD:
    case BFD_RELOC_ALPHA_TLSLDM:
    case BFD_RELOC_ALPHA_GOTDTPREL16:
    case BFD_RELOC_ALPHA_DTPREL_HI16:
    case BFD_RELOC_ALPHA_DTPREL_LO16:
    case BFD_RELOC_ALPHA_DTPREL16:
    case BFD_RELOC_ALPHA_GOTTPREL16:
    case BFD_RELOC_ALPHA_TPREL_HI16:
    case BFD_RELOC_ALPHA_TPREL_LO16:
    case BFD_RELOC_ALPHA_TPREL16:
      if (fixP->fx_addsy)
	S_SET_THREAD_LOCAL (fixP->fx_addsy);
      return;
#endif

#ifdef OBJ_ECOFF
    case BFD_RELOC_ALPHA_LITERAL:
      md_number_to_chars (fixpos, value, 2);
      return;
#endif
    case BFD_RELOC_ALPHA_ELF_LITERAL:
    case BFD_RELOC_ALPHA_LITUSE:
    case BFD_RELOC_ALPHA_LINKAGE:
    case BFD_RELOC_ALPHA_CODEADDR:
      return;

    case BFD_RELOC_VTABLE_INHERIT:
    case BFD_RELOC_VTABLE_ENTRY:
      return;

    default:
      {
	const struct alpha_operand *operand;

	if ((int) fixP->fx_r_type >= 0)
	  as_fatal (_("unhandled relocation type %s"),
		    bfd_get_reloc_code_name (fixP->fx_r_type));

	assert (-(int) fixP->fx_r_type < (int) alpha_num_operands);
	operand = &alpha_operands[-(int) fixP->fx_r_type];

	/* The rest of these fixups only exist internally during symbol
	   resolution and have no representation in the object file.
	   Therefore they must be completely resolved as constants.  */

	if (fixP->fx_addsy != 0
	    && S_GET_SEGMENT (fixP->fx_addsy) != absolute_section)
	  as_bad_where (fixP->fx_file, fixP->fx_line,
			_("non-absolute expression in constant field"));

	image = bfd_getl32 (fixpos);
	image = insert_operand (image, operand, (offsetT) value,
				fixP->fx_file, fixP->fx_line);
      }
      goto write_done;
    }

  if (fixP->fx_addsy != 0 || fixP->fx_pcrel != 0)
    return;
  else
    {
      as_warn_where (fixP->fx_file, fixP->fx_line,
		     _("type %d reloc done?\n"), (int) fixP->fx_r_type);
      goto done;
    }

write_done:
  md_number_to_chars (fixpos, image, 4);

done:
  fixP->fx_done = 1;
}