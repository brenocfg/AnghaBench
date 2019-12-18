#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int fx_r_type; scalar_t__ fx_addsy; scalar_t__ fx_offset; int /*<<< orphan*/  fx_line; int /*<<< orphan*/  fx_file; scalar_t__ fx_pcrel; scalar_t__ fx_where; TYPE_1__* fx_frag; } ;
typedef  TYPE_2__ fixS ;
typedef  scalar_t__ bfd_reloc_code_real_type ;
typedef  int /*<<< orphan*/  asymbol ;
struct TYPE_13__ {scalar_t__ use_rela_p; } ;
typedef  TYPE_3__ asection ;
struct TYPE_14__ {scalar_t__ address; int /*<<< orphan*/ * howto; scalar_t__ addend; TYPE_8__** sym_ptr_ptr; } ;
typedef  TYPE_4__ arelent ;
struct TYPE_15__ {int /*<<< orphan*/  value; } ;
struct TYPE_11__ {scalar_t__ fr_address; } ;

/* Variables and functions */
#define  BFD_RELOC_16 207 
 scalar_t__ BFD_RELOC_16_PCREL ; 
#define  BFD_RELOC_32 206 
 scalar_t__ BFD_RELOC_32_PCREL ; 
#define  BFD_RELOC_32_SECREL 205 
#define  BFD_RELOC_8 204 
 scalar_t__ BFD_RELOC_8_PCREL ; 
#define  BFD_RELOC_ARM_ADRL_IMMEDIATE 203 
#define  BFD_RELOC_ARM_ALU_PC_G0 202 
#define  BFD_RELOC_ARM_ALU_PC_G0_NC 201 
#define  BFD_RELOC_ARM_ALU_PC_G1 200 
#define  BFD_RELOC_ARM_ALU_PC_G1_NC 199 
#define  BFD_RELOC_ARM_ALU_PC_G2 198 
#define  BFD_RELOC_ARM_ALU_SB_G0 197 
#define  BFD_RELOC_ARM_ALU_SB_G0_NC 196 
#define  BFD_RELOC_ARM_ALU_SB_G1 195 
#define  BFD_RELOC_ARM_ALU_SB_G1_NC 194 
#define  BFD_RELOC_ARM_ALU_SB_G2 193 
#define  BFD_RELOC_ARM_CP_OFF_IMM 192 
#define  BFD_RELOC_ARM_GOT32 191 
#define  BFD_RELOC_ARM_GOTOFF 190 
 scalar_t__ BFD_RELOC_ARM_GOTPC ; 
#define  BFD_RELOC_ARM_HWLITERAL 189 
#define  BFD_RELOC_ARM_IMMEDIATE 188 
#define  BFD_RELOC_ARM_LDC_PC_G0 187 
#define  BFD_RELOC_ARM_LDC_PC_G1 186 
#define  BFD_RELOC_ARM_LDC_PC_G2 185 
#define  BFD_RELOC_ARM_LDC_SB_G0 184 
#define  BFD_RELOC_ARM_LDC_SB_G1 183 
#define  BFD_RELOC_ARM_LDC_SB_G2 182 
#define  BFD_RELOC_ARM_LDRS_PC_G0 181 
#define  BFD_RELOC_ARM_LDRS_PC_G1 180 
#define  BFD_RELOC_ARM_LDRS_PC_G2 179 
#define  BFD_RELOC_ARM_LDRS_SB_G0 178 
#define  BFD_RELOC_ARM_LDRS_SB_G1 177 
#define  BFD_RELOC_ARM_LDRS_SB_G2 176 
#define  BFD_RELOC_ARM_LDR_PC_G0 175 
#define  BFD_RELOC_ARM_LDR_PC_G1 174 
#define  BFD_RELOC_ARM_LDR_PC_G2 173 
#define  BFD_RELOC_ARM_LDR_SB_G0 172 
#define  BFD_RELOC_ARM_LDR_SB_G1 171 
#define  BFD_RELOC_ARM_LDR_SB_G2 170 
#define  BFD_RELOC_ARM_LITERAL 169 
#define  BFD_RELOC_ARM_MOVT 168 
 scalar_t__ BFD_RELOC_ARM_MOVT_PCREL ; 
#define  BFD_RELOC_ARM_MOVW 167 
 scalar_t__ BFD_RELOC_ARM_MOVW_PCREL ; 
#define  BFD_RELOC_ARM_MULTI 166 
#define  BFD_RELOC_ARM_OFFSET_IMM 165 
#define  BFD_RELOC_ARM_OFFSET_IMM8 164 
#define  BFD_RELOC_ARM_PCREL_BLX 163 
#define  BFD_RELOC_ARM_PCREL_BRANCH 162 
#define  BFD_RELOC_ARM_PCREL_CALL 161 
#define  BFD_RELOC_ARM_PCREL_JUMP 160 
#define  BFD_RELOC_ARM_PLT32 159 
#define  BFD_RELOC_ARM_PREL31 158 
#define  BFD_RELOC_ARM_ROSEGREL32 157 
#define  BFD_RELOC_ARM_SBREL32 156 
#define  BFD_RELOC_ARM_SHIFT_IMM 155 
#define  BFD_RELOC_ARM_SMC 154 
#define  BFD_RELOC_ARM_SWI 153 
#define  BFD_RELOC_ARM_T32_CP_OFF_IMM 152 
#define  BFD_RELOC_ARM_TARGET1 151 
#define  BFD_RELOC_ARM_TARGET2 150 
#define  BFD_RELOC_ARM_THUMB_ADD 149 
#define  BFD_RELOC_ARM_THUMB_IMM 148 
#define  BFD_RELOC_ARM_THUMB_MOVT 147 
 scalar_t__ BFD_RELOC_ARM_THUMB_MOVT_PCREL ; 
#define  BFD_RELOC_ARM_THUMB_MOVW 146 
 scalar_t__ BFD_RELOC_ARM_THUMB_MOVW_PCREL ; 
#define  BFD_RELOC_ARM_THUMB_OFFSET 145 
#define  BFD_RELOC_ARM_THUMB_SHIFT 144 
#define  BFD_RELOC_ARM_TLS_GD32 143 
#define  BFD_RELOC_ARM_TLS_IE32 142 
#define  BFD_RELOC_ARM_TLS_LDM32 141 
#define  BFD_RELOC_ARM_TLS_LDO32 140 
#define  BFD_RELOC_ARM_TLS_LE32 139 
#define  BFD_RELOC_NONE 138 
#define  BFD_RELOC_RVA 137 
#define  BFD_RELOC_THUMB_PCREL_BLX 136 
#define  BFD_RELOC_THUMB_PCREL_BRANCH12 135 
#define  BFD_RELOC_THUMB_PCREL_BRANCH20 134 
#define  BFD_RELOC_THUMB_PCREL_BRANCH23 133 
#define  BFD_RELOC_THUMB_PCREL_BRANCH25 132 
#define  BFD_RELOC_THUMB_PCREL_BRANCH7 131 
#define  BFD_RELOC_THUMB_PCREL_BRANCH9 130 
#define  BFD_RELOC_VTABLE_ENTRY 129 
#define  BFD_RELOC_VTABLE_INHERIT 128 
 scalar_t__ GOT_symbol ; 
 char* S_GET_NAME (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_IS_COMMON (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_IS_DEFINED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_IS_LOCAL (int /*<<< orphan*/ *) ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  as_bad_where (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 char* bfd_get_reloc_code_name (scalar_t__) ; 
 int /*<<< orphan*/ * bfd_reloc_type_lookup (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ md_pcrel_from_section (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  stdoutput ; 
 TYPE_8__* symbol_get_bfdsym (int /*<<< orphan*/ *) ; 
 void* xmalloc (int) ; 

arelent *
tc_gen_reloc (asection *section, fixS *fixp)
{
  arelent * reloc;
  bfd_reloc_code_real_type code;

  reloc = xmalloc (sizeof (arelent));

  reloc->sym_ptr_ptr = xmalloc (sizeof (asymbol *));
  *reloc->sym_ptr_ptr = symbol_get_bfdsym (fixp->fx_addsy);
  reloc->address = fixp->fx_frag->fr_address + fixp->fx_where;

  if (fixp->fx_pcrel)
    {
      if (section->use_rela_p)
	fixp->fx_offset -= md_pcrel_from_section (fixp, section);
      else
	fixp->fx_offset = reloc->address;
    }
  reloc->addend = fixp->fx_offset;

  switch (fixp->fx_r_type)
    {
    case BFD_RELOC_8:
      if (fixp->fx_pcrel)
	{
	  code = BFD_RELOC_8_PCREL;
	  break;
	}

    case BFD_RELOC_16:
      if (fixp->fx_pcrel)
	{
	  code = BFD_RELOC_16_PCREL;
	  break;
	}

    case BFD_RELOC_32:
      if (fixp->fx_pcrel)
	{
	  code = BFD_RELOC_32_PCREL;
	  break;
	}

    case BFD_RELOC_ARM_MOVW:
      if (fixp->fx_pcrel)
	{
	  code = BFD_RELOC_ARM_MOVW_PCREL;
	  break;
	}

    case BFD_RELOC_ARM_MOVT:
      if (fixp->fx_pcrel)
	{
	  code = BFD_RELOC_ARM_MOVT_PCREL;
	  break;
	}

    case BFD_RELOC_ARM_THUMB_MOVW:
      if (fixp->fx_pcrel)
	{
	  code = BFD_RELOC_ARM_THUMB_MOVW_PCREL;
	  break;
	}

    case BFD_RELOC_ARM_THUMB_MOVT:
      if (fixp->fx_pcrel)
	{
	  code = BFD_RELOC_ARM_THUMB_MOVT_PCREL;
	  break;
	}

    case BFD_RELOC_NONE:
    case BFD_RELOC_ARM_PCREL_BRANCH:
    case BFD_RELOC_ARM_PCREL_BLX:
    case BFD_RELOC_RVA:
    case BFD_RELOC_THUMB_PCREL_BRANCH7:
    case BFD_RELOC_THUMB_PCREL_BRANCH9:
    case BFD_RELOC_THUMB_PCREL_BRANCH12:
    case BFD_RELOC_THUMB_PCREL_BRANCH20:
    case BFD_RELOC_THUMB_PCREL_BRANCH23:
    case BFD_RELOC_THUMB_PCREL_BRANCH25:
    case BFD_RELOC_THUMB_PCREL_BLX:
    case BFD_RELOC_VTABLE_ENTRY:
    case BFD_RELOC_VTABLE_INHERIT:
#ifdef TE_PE
    case BFD_RELOC_32_SECREL:
#endif
      code = fixp->fx_r_type;
      break;

    case BFD_RELOC_ARM_LITERAL:
    case BFD_RELOC_ARM_HWLITERAL:
      /* If this is called then the a literal has
	 been referenced across a section boundary.  */
      as_bad_where (fixp->fx_file, fixp->fx_line,
		    _("literal referenced across section boundary"));
      return NULL;

#ifdef OBJ_ELF
    case BFD_RELOC_ARM_GOT32:
    case BFD_RELOC_ARM_GOTOFF:
    case BFD_RELOC_ARM_PLT32:
    case BFD_RELOC_ARM_TARGET1:
    case BFD_RELOC_ARM_ROSEGREL32:
    case BFD_RELOC_ARM_SBREL32:
    case BFD_RELOC_ARM_PREL31:
    case BFD_RELOC_ARM_TARGET2:
    case BFD_RELOC_ARM_TLS_LE32:
    case BFD_RELOC_ARM_TLS_LDO32:
    case BFD_RELOC_ARM_PCREL_CALL:
    case BFD_RELOC_ARM_PCREL_JUMP:
    case BFD_RELOC_ARM_ALU_PC_G0_NC:
    case BFD_RELOC_ARM_ALU_PC_G0:
    case BFD_RELOC_ARM_ALU_PC_G1_NC:
    case BFD_RELOC_ARM_ALU_PC_G1:
    case BFD_RELOC_ARM_ALU_PC_G2:
    case BFD_RELOC_ARM_LDR_PC_G0:
    case BFD_RELOC_ARM_LDR_PC_G1:
    case BFD_RELOC_ARM_LDR_PC_G2:
    case BFD_RELOC_ARM_LDRS_PC_G0:
    case BFD_RELOC_ARM_LDRS_PC_G1:
    case BFD_RELOC_ARM_LDRS_PC_G2:
    case BFD_RELOC_ARM_LDC_PC_G0:
    case BFD_RELOC_ARM_LDC_PC_G1:
    case BFD_RELOC_ARM_LDC_PC_G2:
    case BFD_RELOC_ARM_ALU_SB_G0_NC:
    case BFD_RELOC_ARM_ALU_SB_G0:
    case BFD_RELOC_ARM_ALU_SB_G1_NC:
    case BFD_RELOC_ARM_ALU_SB_G1:
    case BFD_RELOC_ARM_ALU_SB_G2:
    case BFD_RELOC_ARM_LDR_SB_G0:
    case BFD_RELOC_ARM_LDR_SB_G1:
    case BFD_RELOC_ARM_LDR_SB_G2:
    case BFD_RELOC_ARM_LDRS_SB_G0:
    case BFD_RELOC_ARM_LDRS_SB_G1:
    case BFD_RELOC_ARM_LDRS_SB_G2:
    case BFD_RELOC_ARM_LDC_SB_G0:
    case BFD_RELOC_ARM_LDC_SB_G1:
    case BFD_RELOC_ARM_LDC_SB_G2:
      code = fixp->fx_r_type;
      break;

    case BFD_RELOC_ARM_TLS_GD32:
    case BFD_RELOC_ARM_TLS_IE32:
    case BFD_RELOC_ARM_TLS_LDM32:
      /* BFD will include the symbol's address in the addend.
	 But we don't want that, so subtract it out again here.  */
      if (!S_IS_COMMON (fixp->fx_addsy))
	reloc->addend -= (*reloc->sym_ptr_ptr)->value;
      code = fixp->fx_r_type;
      break;
#endif

    case BFD_RELOC_ARM_IMMEDIATE:
      as_bad_where (fixp->fx_file, fixp->fx_line,
		    _("internal relocation (type: IMMEDIATE) not fixed up"));
      return NULL;

    case BFD_RELOC_ARM_ADRL_IMMEDIATE:
      as_bad_where (fixp->fx_file, fixp->fx_line,
		    _("ADRL used for a symbol not defined in the same file"));
      return NULL;

    case BFD_RELOC_ARM_OFFSET_IMM:
      if (section->use_rela_p)
	{
	  code = fixp->fx_r_type;
	  break;
	}

      if (fixp->fx_addsy != NULL
	  && !S_IS_DEFINED (fixp->fx_addsy)
	  && S_IS_LOCAL (fixp->fx_addsy))
	{
	  as_bad_where (fixp->fx_file, fixp->fx_line,
			_("undefined local label `%s'"),
			S_GET_NAME (fixp->fx_addsy));
	  return NULL;
	}

      as_bad_where (fixp->fx_file, fixp->fx_line,
		    _("internal_relocation (type: OFFSET_IMM) not fixed up"));
      return NULL;

    default:
      {
	char * type;

	switch (fixp->fx_r_type)
	  {
	  case BFD_RELOC_NONE:		   type = "NONE";	  break;
	  case BFD_RELOC_ARM_OFFSET_IMM8:  type = "OFFSET_IMM8";  break;
	  case BFD_RELOC_ARM_SHIFT_IMM:	   type = "SHIFT_IMM";	  break;
	  case BFD_RELOC_ARM_SMC:	   type = "SMC";	  break;
	  case BFD_RELOC_ARM_SWI:	   type = "SWI";	  break;
	  case BFD_RELOC_ARM_MULTI:	   type = "MULTI";	  break;
	  case BFD_RELOC_ARM_CP_OFF_IMM:   type = "CP_OFF_IMM";	  break;
	  case BFD_RELOC_ARM_T32_CP_OFF_IMM: type = "T32_CP_OFF_IMM"; break;
	  case BFD_RELOC_ARM_THUMB_ADD:	   type = "THUMB_ADD";	  break;
	  case BFD_RELOC_ARM_THUMB_SHIFT:  type = "THUMB_SHIFT";  break;
	  case BFD_RELOC_ARM_THUMB_IMM:	   type = "THUMB_IMM";	  break;
	  case BFD_RELOC_ARM_THUMB_OFFSET: type = "THUMB_OFFSET"; break;
	  default:			   type = _("<unknown>"); break;
	  }
	as_bad_where (fixp->fx_file, fixp->fx_line,
		      _("cannot represent %s relocation in this object file format"),
		      type);
	return NULL;
      }
    }

#ifdef OBJ_ELF
  if ((code == BFD_RELOC_32_PCREL || code == BFD_RELOC_32)
      && GOT_symbol
      && fixp->fx_addsy == GOT_symbol)
    {
      code = BFD_RELOC_ARM_GOTPC;
      reloc->addend = fixp->fx_offset = reloc->address;
    }
#endif

  reloc->howto = bfd_reloc_type_lookup (stdoutput, code);

  if (reloc->howto == NULL)
    {
      as_bad_where (fixp->fx_file, fixp->fx_line,
		    _("cannot represent %s relocation in this object file format"),
		    bfd_get_reloc_code_name (code));
      return NULL;
    }

  /* HACK: Since arm ELF uses Rel instead of Rela, encode the
     vtable entry to be used in the relocation's section offset.  */
  if (fixp->fx_r_type == BFD_RELOC_VTABLE_ENTRY)
    reloc->address = fixp->fx_offset;

  return reloc;
}