#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct disassemble_info {int symtab_pos; int symtab_size; scalar_t__ section; int bytes_per_line; unsigned int bytes_per_chunk; int (* read_memory_func ) (int,int /*<<< orphan*/ *,unsigned int,struct disassemble_info*) ;int flags; int /*<<< orphan*/  (* memory_error_func ) (int,int,struct disassemble_info*) ;int /*<<< orphan*/  display_endian; TYPE_8__** symbols; TYPE_8__** symtab; int /*<<< orphan*/ * disassembler_options; } ;
typedef  enum map_type { ____Placeholder_map_type } map_type ;
struct TYPE_11__ {int /*<<< orphan*/  st_info; } ;
struct TYPE_15__ {TYPE_1__ internal_elf_sym; } ;
typedef  TYPE_5__ elf_symbol_type ;
struct TYPE_16__ {TYPE_4__* native; } ;
typedef  TYPE_6__ coff_symbol_type ;
typedef  int bfd_vma ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  void* bfd_boolean ;
struct TYPE_17__ {scalar_t__ section; } ;
struct TYPE_13__ {scalar_t__ n_sclass; } ;
struct TYPE_12__ {TYPE_3__ syment; } ;
struct TYPE_14__ {TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ENDIAN_BIG ; 
 int /*<<< orphan*/  BFD_ENDIAN_LITTLE ; 
 scalar_t__ C_THUMBEXT ; 
 scalar_t__ C_THUMBEXTFUNC ; 
 scalar_t__ C_THUMBLABEL ; 
 scalar_t__ C_THUMBSTAT ; 
 scalar_t__ C_THUMBSTATFUNC ; 
 unsigned int ELF_ST_TYPE (int /*<<< orphan*/ ) ; 
 void* FALSE ; 
 int INSN_HAS_RELOC ; 
 int MAP_ARM ; 
 scalar_t__ MAP_DATA ; 
 scalar_t__ MAP_THUMB ; 
 unsigned int STT_ARM_16BIT ; 
 unsigned int STT_ARM_TFUNC ; 
 void* TRUE ; 
 scalar_t__ bfd_asymbol_flavour (TYPE_8__*) ; 
 int bfd_asymbol_value (TYPE_8__*) ; 
 scalar_t__ bfd_target_coff_flavour ; 
 scalar_t__ bfd_target_elf_flavour ; 
 TYPE_6__* coffsymbol (TYPE_8__*) ; 
 int /*<<< orphan*/  find_ifthen_state (int,struct disassemble_info*,void*) ; 
 scalar_t__ force_thumb ; 
 scalar_t__ get_sym_code_type (struct disassemble_info*,int,int*) ; 
 int ifthen_address ; 
 int ifthen_next_state ; 
 int ifthen_state ; 
 int last_mapping_addr ; 
 int last_mapping_sym ; 
 scalar_t__ last_type ; 
 int /*<<< orphan*/  parse_disassembler_options (int /*<<< orphan*/ *) ; 
 void print_insn_arm (int,struct disassemble_info*,long) ; 
 void print_insn_data (int,struct disassemble_info*,long) ; 
 void print_insn_thumb16 (int,struct disassemble_info*,long) ; 
 void print_insn_thumb32 (int,struct disassemble_info*,long) ; 
 int stub1 (int,int /*<<< orphan*/ *,unsigned int,struct disassemble_info*) ; 
 int stub2 (int,int /*<<< orphan*/ *,int,struct disassemble_info*) ; 
 int stub3 (int,int /*<<< orphan*/ *,int,struct disassemble_info*) ; 
 int stub4 (int,int /*<<< orphan*/ *,int,struct disassemble_info*) ; 
 int /*<<< orphan*/  stub5 (int,int,struct disassemble_info*) ; 

__attribute__((used)) static int
print_insn (bfd_vma pc, struct disassemble_info *info, bfd_boolean little)
{
  unsigned char b[4];
  long		given;
  int           status;
  int           is_thumb = FALSE;
  int           is_data = FALSE;
  unsigned int	size = 4;
  void	 	(*printer) (bfd_vma, struct disassemble_info *, long);
  bfd_boolean   found = FALSE;

  if (info->disassembler_options)
    {
      parse_disassembler_options (info->disassembler_options);

      /* To avoid repeated parsing of these options, we remove them here.  */
      info->disassembler_options = NULL;
    }

  /* First check the full symtab for a mapping symbol, even if there
     are no usable non-mapping symbols for this address.  */
  if (info->symtab != NULL
      && bfd_asymbol_flavour (*info->symtab) == bfd_target_elf_flavour)
    {
      bfd_vma addr;
      int n;
      int last_sym = -1;
      enum map_type type = MAP_ARM;

      if (pc <= last_mapping_addr)
	last_mapping_sym = -1;
      is_thumb = (last_type == MAP_THUMB);
      found = FALSE;
      /* Start scanning at the start of the function, or wherever
	 we finished last time.  */
      n = info->symtab_pos + 1;
      if (n < last_mapping_sym)
	n = last_mapping_sym;

      /* Scan up to the location being disassembled.  */
      for (; n < info->symtab_size; n++)
	{
	  addr = bfd_asymbol_value (info->symtab[n]);
	  if (addr > pc)
	    break;
	  if ((info->section == NULL
	       || info->section == info->symtab[n]->section)
	      && get_sym_code_type (info, n, &type))
	    {
	      last_sym = n;
	      found = TRUE;
	    }
	}

      if (!found)
	{
	  n = info->symtab_pos;
	  if (n < last_mapping_sym - 1)
	    n = last_mapping_sym - 1;

	  /* No mapping symbol found at this address.  Look backwards
	     for a preceeding one.  */
	  for (; n >= 0; n--)
	    {
	      if (get_sym_code_type (info, n, &type))
		{
		  last_sym = n;
		  found = TRUE;
		  break;
		}
	    }
	}

      last_mapping_sym = last_sym;
      last_type = type;
      is_thumb = (last_type == MAP_THUMB);
      is_data = (last_type == MAP_DATA);

      /* Look a little bit ahead to see if we should print out
	 two or four bytes of data.  If there's a symbol,
	 mapping or otherwise, after two bytes then don't
	 print more.  */
      if (is_data)
	{
	  size = 4 - (pc & 3);
	  for (n = last_sym + 1; n < info->symtab_size; n++)
	    {
	      addr = bfd_asymbol_value (info->symtab[n]);
	      if (addr > pc)
		{
		  if (addr - pc < size)
		    size = addr - pc;
		  break;
		}
	    }
	  /* If the next symbol is after three bytes, we need to
	     print only part of the data, so that we can use either
	     .byte or .short.  */
	  if (size == 3)
	    size = (pc & 1) ? 1 : 2;
	}
    }

  if (info->symbols != NULL)
    {
      if (bfd_asymbol_flavour (*info->symbols) == bfd_target_coff_flavour)
	{
	  coff_symbol_type * cs;

	  cs = coffsymbol (*info->symbols);
	  is_thumb = (   cs->native->u.syment.n_sclass == C_THUMBEXT
		      || cs->native->u.syment.n_sclass == C_THUMBSTAT
		      || cs->native->u.syment.n_sclass == C_THUMBLABEL
		      || cs->native->u.syment.n_sclass == C_THUMBEXTFUNC
		      || cs->native->u.syment.n_sclass == C_THUMBSTATFUNC);
	}
      else if (bfd_asymbol_flavour (*info->symbols) == bfd_target_elf_flavour
	       && !found)
	{
	  /* If no mapping symbol has been found then fall back to the type
	     of the function symbol.  */
	  elf_symbol_type *  es;
	  unsigned int       type;

	  es = *(elf_symbol_type **)(info->symbols);
	  type = ELF_ST_TYPE (es->internal_elf_sym.st_info);

	  is_thumb = (type == STT_ARM_TFUNC) || (type == STT_ARM_16BIT);
	}
    }

  if (force_thumb)
    is_thumb = TRUE;

  info->display_endian = little ? BFD_ENDIAN_LITTLE : BFD_ENDIAN_BIG;
  info->bytes_per_line = 4;

  if (is_data)
    {
      int i;

      /* size was already set above.  */
      info->bytes_per_chunk = size;
      printer = print_insn_data;

      status = info->read_memory_func (pc, (bfd_byte *)b, size, info);
      given = 0;
      if (little)
	for (i = size - 1; i >= 0; i--)
	  given = b[i] | (given << 8);
      else
	for (i = 0; i < (int) size; i++)
	  given = b[i] | (given << 8);
    }
  else if (!is_thumb)
    {
      /* In ARM mode endianness is a straightforward issue: the instruction
	 is four bytes long and is either ordered 0123 or 3210.  */
      printer = print_insn_arm;
      info->bytes_per_chunk = 4;
      size = 4;

      status = info->read_memory_func (pc, (bfd_byte *)b, 4, info);
      if (little)
	given = (b[0]) | (b[1] << 8) | (b[2] << 16) | (b[3] << 24);
      else
	given = (b[3]) | (b[2] << 8) | (b[1] << 16) | (b[0] << 24);
    }
  else
    {
      /* In Thumb mode we have the additional wrinkle of two
	 instruction lengths.  Fortunately, the bits that determine
	 the length of the current instruction are always to be found
	 in the first two bytes.  */
      printer = print_insn_thumb16;
      info->bytes_per_chunk = 2;
      size = 2;

      status = info->read_memory_func (pc, (bfd_byte *)b, 2, info);
      if (little)
	given = (b[0]) | (b[1] << 8);
      else
	given = (b[1]) | (b[0] << 8);

      if (!status)
	{
	  /* These bit patterns signal a four-byte Thumb
	     instruction.  */
	  if ((given & 0xF800) == 0xF800
	      || (given & 0xF800) == 0xF000
	      || (given & 0xF800) == 0xE800)
	    {
	      status = info->read_memory_func (pc + 2, (bfd_byte *)b, 2, info);
	      if (little)
		given = (b[0]) | (b[1] << 8) | (given << 16);
	      else
		given = (b[1]) | (b[0] << 8) | (given << 16);

	      printer = print_insn_thumb32;
	      size = 4;
	    }
	}

      if (ifthen_address != pc)
	find_ifthen_state(pc, info, little);

      if (ifthen_state)
	{
	  if ((ifthen_state & 0xf) == 0x8)
	    ifthen_next_state = 0;
	  else
	    ifthen_next_state = (ifthen_state & 0xe0)
				| ((ifthen_state & 0xf) << 1);
	}
    }

  if (status)
    {
      info->memory_error_func (status, pc, info);
      return -1;
    }
  if (info->flags & INSN_HAS_RELOC)
    /* If the instruction has a reloc associated with it, then
       the offset field in the instruction will actually be the
       addend for the reloc.  (We are using REL type relocs).
       In such cases, we can ignore the pc when computing
       addresses, since the addend is not currently pc-relative.  */
    pc = 0;

  printer (pc, info, given);

  if (is_thumb)
    {
      ifthen_state = ifthen_next_state;
      ifthen_address += size;
    }
  return size;
}