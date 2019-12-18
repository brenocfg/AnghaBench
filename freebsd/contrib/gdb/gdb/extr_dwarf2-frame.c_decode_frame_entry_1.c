#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dwarf2_fde {char* instructions; char* end; TYPE_2__* cie; void* address_range; void* initial_location; } ;
struct dwarf2_cie {char* initial_instructions; int saw_z_augmentation; char* end; int /*<<< orphan*/  encoding; scalar_t__ return_address_register; int /*<<< orphan*/  data_alignment_factor; void* code_alignment_factor; scalar_t__ cie_pointer; } ;
struct comp_unit {char* dwarf_frame_buffer; int dwarf_frame_size; int /*<<< orphan*/  abfd; TYPE_1__* objfile; int /*<<< orphan*/  addr_size; } ;
typedef  scalar_t__ ULONGEST ;
struct TYPE_4__ {int encoding; scalar_t__ saw_z_augmentation; } ;
struct TYPE_3__ {int /*<<< orphan*/  objfile_obstack; } ;
typedef  int LONGEST ;

/* Variables and functions */
 scalar_t__ DW64_CIE_ID ; 
 scalar_t__ DW_CIE_ID ; 
 scalar_t__ DW_CIE_VERSION ; 
 int /*<<< orphan*/  TYPE_LENGTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_cie (struct comp_unit*,struct dwarf2_cie*) ; 
 int /*<<< orphan*/  add_fde (struct comp_unit*,struct dwarf2_fde*) ; 
 int /*<<< orphan*/  builtin_type_void_data_ptr ; 
 int /*<<< orphan*/  decode_frame_entry (struct comp_unit*,char*,int) ; 
 int /*<<< orphan*/  encoding_for_size (int /*<<< orphan*/ ) ; 
 void* find_cie (struct comp_unit*,scalar_t__) ; 
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ obstack_alloc (int /*<<< orphan*/ *,int) ; 
 scalar_t__ read_1_byte (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ read_4_bytes (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ read_8_bytes (int /*<<< orphan*/ ,char*) ; 
 void* read_encoded_value (struct comp_unit*,int,char*,unsigned int*) ; 
 int read_initial_length (int /*<<< orphan*/ ,char*,unsigned int*) ; 
 int /*<<< orphan*/  read_signed_leb128 (int /*<<< orphan*/ ,char*,unsigned int*) ; 
 void* read_unsigned_leb128 (int /*<<< orphan*/ ,char*,unsigned int*) ; 
 int /*<<< orphan*/  size_of_encoded_value (int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 

__attribute__((used)) static char *
decode_frame_entry_1 (struct comp_unit *unit, char *start, int eh_frame_p)
{
  char *buf;
  LONGEST length;
  unsigned int bytes_read;
  int dwarf64_p;
  ULONGEST cie_id;
  ULONGEST cie_pointer;
  char *end;

  buf = start;
  length = read_initial_length (unit->abfd, buf, &bytes_read);
  buf += bytes_read;
  end = buf + length;

  /* Are we still within the section? */
  if (end > unit->dwarf_frame_buffer + unit->dwarf_frame_size)
    return NULL;

  if (length == 0)
    return end;

  /* Distinguish between 32 and 64-bit encoded frame info.  */
  dwarf64_p = (bytes_read == 12);

  /* In a .eh_frame section, zero is used to distinguish CIEs from FDEs.  */
  if (eh_frame_p)
    cie_id = 0;
  else if (dwarf64_p)
    cie_id = DW64_CIE_ID;
  else
    cie_id = DW_CIE_ID;

  if (dwarf64_p)
    {
      cie_pointer = read_8_bytes (unit->abfd, buf);
      buf += 8;
    }
  else
    {
      cie_pointer = read_4_bytes (unit->abfd, buf);
      buf += 4;
    }

  if (cie_pointer == cie_id)
    {
      /* This is a CIE.  */
      struct dwarf2_cie *cie;
      char *augmentation;

      /* Record the offset into the .debug_frame section of this CIE.  */
      cie_pointer = start - unit->dwarf_frame_buffer;

      /* Check whether we've already read it.  */
      if (find_cie (unit, cie_pointer))
	return end;

      cie = (struct dwarf2_cie *)
	obstack_alloc (&unit->objfile->objfile_obstack,
		       sizeof (struct dwarf2_cie));
      cie->initial_instructions = NULL;
      cie->cie_pointer = cie_pointer;

      /* The encoding for FDE's in a normal .debug_frame section
         depends on the target address size as specified in the
         Compilation Unit Header.  */
      cie->encoding = encoding_for_size (unit->addr_size);

      /* Check version number.  */
      if (read_1_byte (unit->abfd, buf) != DW_CIE_VERSION)
	return NULL;
      buf += 1;

      /* Interpret the interesting bits of the augmentation.  */
      augmentation = buf;
      buf = augmentation + strlen (augmentation) + 1;

      /* The GCC 2.x "eh" augmentation has a pointer immediately
         following the augmentation string, so it must be handled
         first.  */
      if (augmentation[0] == 'e' && augmentation[1] == 'h')
	{
	  /* Skip.  */
	  buf += TYPE_LENGTH (builtin_type_void_data_ptr);
	  augmentation += 2;
	}

      cie->code_alignment_factor =
	read_unsigned_leb128 (unit->abfd, buf, &bytes_read);
      buf += bytes_read;

      cie->data_alignment_factor =
	read_signed_leb128 (unit->abfd, buf, &bytes_read);
      buf += bytes_read;

      cie->return_address_register = read_1_byte (unit->abfd, buf);
      buf += 1;

      cie->saw_z_augmentation = (*augmentation == 'z');
      if (cie->saw_z_augmentation)
	{
	  ULONGEST length;

	  length = read_unsigned_leb128 (unit->abfd, buf, &bytes_read);
	  buf += bytes_read;
	  if (buf > end)
	    return NULL;
	  cie->initial_instructions = buf + length;
	  augmentation++;
	}

      while (*augmentation)
	{
	  /* "L" indicates a byte showing how the LSDA pointer is encoded.  */
	  if (*augmentation == 'L')
	    {
	      /* Skip.  */
	      buf++;
	      augmentation++;
	    }

	  /* "R" indicates a byte indicating how FDE addresses are encoded.  */
	  else if (*augmentation == 'R')
	    {
	      cie->encoding = *buf++;
	      augmentation++;
	    }

	  /* "P" indicates a personality routine in the CIE augmentation.  */
	  else if (*augmentation == 'P')
	    {
	      /* Skip.  */
	      buf += size_of_encoded_value (*buf++);
	      augmentation++;
	    }

	  /* Otherwise we have an unknown augmentation.
	     Bail out unless we saw a 'z' prefix.  */
	  else
	    {
	      if (cie->initial_instructions == NULL)
		return end;

	      /* Skip unknown augmentations.  */
	      buf = cie->initial_instructions;
	      break;
	    }
	}

      cie->initial_instructions = buf;
      cie->end = end;

      add_cie (unit, cie);
    }
  else
    {
      /* This is a FDE.  */
      struct dwarf2_fde *fde;

      /* In an .eh_frame section, the CIE pointer is the delta between the
	 address within the FDE where the CIE pointer is stored and the
	 address of the CIE.  Convert it to an offset into the .eh_frame
	 section.  */
      if (eh_frame_p)
	{
	  cie_pointer = buf - unit->dwarf_frame_buffer - cie_pointer;
	  cie_pointer -= (dwarf64_p ? 8 : 4);
	}

      /* In either case, validate the result is still within the section.  */
      if (cie_pointer >= unit->dwarf_frame_size)
	return NULL;

      fde = (struct dwarf2_fde *)
	obstack_alloc (&unit->objfile->objfile_obstack,
		       sizeof (struct dwarf2_fde));
      fde->cie = find_cie (unit, cie_pointer);
      if (fde->cie == NULL)
	{
	  decode_frame_entry (unit, unit->dwarf_frame_buffer + cie_pointer,
			      eh_frame_p);
	  fde->cie = find_cie (unit, cie_pointer);
	}

      gdb_assert (fde->cie != NULL);

      fde->initial_location =
	read_encoded_value (unit, fde->cie->encoding, buf, &bytes_read);
      buf += bytes_read;

      fde->address_range =
	read_encoded_value (unit, fde->cie->encoding & 0x0f, buf, &bytes_read);
      buf += bytes_read;

      /* A 'z' augmentation in the CIE implies the presence of an
	 augmentation field in the FDE as well.  The only thing known
	 to be in here at present is the LSDA entry for EH.  So we
	 can skip the whole thing.  */
      if (fde->cie->saw_z_augmentation)
	{
	  ULONGEST length;

	  length = read_unsigned_leb128 (unit->abfd, buf, &bytes_read);
	  buf += bytes_read + length;
	  if (buf > end)
	    return NULL;
	}

      fde->instructions = buf;
      fde->end = end;

      add_fde (unit, fde);
    }

  return end;
}