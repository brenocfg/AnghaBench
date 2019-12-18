#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_7__ {int /*<<< orphan*/ * tdata; } ;
struct TYPE_10__ {TYPE_1__ u; } ;
struct TYPE_9__ {int size; scalar_t__ kind; } ;
struct TYPE_8__ {scalar_t__ sh_type; int sh_size; int sh_flags; unsigned int sh_addralign; scalar_t__ sh_entsize; int /*<<< orphan*/ * bfd_section; scalar_t__ sh_offset; int /*<<< orphan*/ * contents; } ;
typedef  TYPE_2__ Elf_Internal_Shdr ;
typedef  TYPE_3__ Elf_Internal_Options ;
typedef  int /*<<< orphan*/  Elf_External_Options ;
typedef  int /*<<< orphan*/  Elf64_External_RegInfo ;
typedef  int /*<<< orphan*/  Elf32_External_RegInfo ;

/* Variables and functions */
 scalar_t__ ABI_64_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  H_PUT_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  H_PUT_64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MIPS_ELF_OPTIONS_SECTION_NAME (int /*<<< orphan*/ *) ; 
 scalar_t__ ODK_REGINFO ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int SHF_ALLOC ; 
 int SHF_MIPS_GPREL ; 
 int SHF_WRITE ; 
 scalar_t__ SHT_MIPS_OPTIONS ; 
 scalar_t__ SHT_MIPS_REGINFO ; 
 scalar_t__ SHT_NOBITS ; 
 void* SHT_PROGBITS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int bfd_bwrite (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 char* bfd_get_section_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_mips_elf_swap_options_in (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ bfd_seek (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elf_gp (int /*<<< orphan*/ *) ; 
 TYPE_4__* mips_elf_section_data (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

bfd_boolean
_bfd_mips_elf_section_processing (bfd *abfd, Elf_Internal_Shdr *hdr)
{
  if (hdr->sh_type == SHT_MIPS_REGINFO
      && hdr->sh_size > 0)
    {
      bfd_byte buf[4];

      BFD_ASSERT (hdr->sh_size == sizeof (Elf32_External_RegInfo));
      BFD_ASSERT (hdr->contents == NULL);

      if (bfd_seek (abfd,
		    hdr->sh_offset + sizeof (Elf32_External_RegInfo) - 4,
		    SEEK_SET) != 0)
	return FALSE;
      H_PUT_32 (abfd, elf_gp (abfd), buf);
      if (bfd_bwrite (buf, 4, abfd) != 4)
	return FALSE;
    }

  if (hdr->sh_type == SHT_MIPS_OPTIONS
      && hdr->bfd_section != NULL
      && mips_elf_section_data (hdr->bfd_section) != NULL
      && mips_elf_section_data (hdr->bfd_section)->u.tdata != NULL)
    {
      bfd_byte *contents, *l, *lend;

      /* We stored the section contents in the tdata field in the
	 set_section_contents routine.  We save the section contents
	 so that we don't have to read them again.
	 At this point we know that elf_gp is set, so we can look
	 through the section contents to see if there is an
	 ODK_REGINFO structure.  */

      contents = mips_elf_section_data (hdr->bfd_section)->u.tdata;
      l = contents;
      lend = contents + hdr->sh_size;
      while (l + sizeof (Elf_External_Options) <= lend)
	{
	  Elf_Internal_Options intopt;

	  bfd_mips_elf_swap_options_in (abfd, (Elf_External_Options *) l,
					&intopt);
	  if (intopt.size < sizeof (Elf_External_Options))
	    {
	      (*_bfd_error_handler)
		(_("%B: Warning: bad `%s' option size %u smaller than its header"),
		abfd, MIPS_ELF_OPTIONS_SECTION_NAME (abfd), intopt.size);
	      break;
	    }
	  if (ABI_64_P (abfd) && intopt.kind == ODK_REGINFO)
	    {
	      bfd_byte buf[8];

	      if (bfd_seek (abfd,
			    (hdr->sh_offset
			     + (l - contents)
			     + sizeof (Elf_External_Options)
			     + (sizeof (Elf64_External_RegInfo) - 8)),
			     SEEK_SET) != 0)
		return FALSE;
	      H_PUT_64 (abfd, elf_gp (abfd), buf);
	      if (bfd_bwrite (buf, 8, abfd) != 8)
		return FALSE;
	    }
	  else if (intopt.kind == ODK_REGINFO)
	    {
	      bfd_byte buf[4];

	      if (bfd_seek (abfd,
			    (hdr->sh_offset
			     + (l - contents)
			     + sizeof (Elf_External_Options)
			     + (sizeof (Elf32_External_RegInfo) - 4)),
			    SEEK_SET) != 0)
		return FALSE;
	      H_PUT_32 (abfd, elf_gp (abfd), buf);
	      if (bfd_bwrite (buf, 4, abfd) != 4)
		return FALSE;
	    }
	  l += intopt.size;
	}
    }

  if (hdr->bfd_section != NULL)
    {
      const char *name = bfd_get_section_name (abfd, hdr->bfd_section);

      if (strcmp (name, ".sdata") == 0
	  || strcmp (name, ".lit8") == 0
	  || strcmp (name, ".lit4") == 0)
	{
	  hdr->sh_flags |= SHF_ALLOC | SHF_WRITE | SHF_MIPS_GPREL;
	  hdr->sh_type = SHT_PROGBITS;
	}
      else if (strcmp (name, ".sbss") == 0)
	{
	  hdr->sh_flags |= SHF_ALLOC | SHF_WRITE | SHF_MIPS_GPREL;
	  hdr->sh_type = SHT_NOBITS;
	}
      else if (strcmp (name, ".srdata") == 0)
	{
	  hdr->sh_flags |= SHF_ALLOC | SHF_MIPS_GPREL;
	  hdr->sh_type = SHT_PROGBITS;
	}
      else if (strcmp (name, ".compact_rel") == 0)
	{
	  hdr->sh_flags = 0;
	  hdr->sh_type = SHT_PROGBITS;
	}
      else if (strcmp (name, ".rtproc") == 0)
	{
	  if (hdr->sh_addralign != 0 && hdr->sh_entsize == 0)
	    {
	      unsigned int adjust;

	      adjust = hdr->sh_size % hdr->sh_addralign;
	      if (adjust != 0)
		hdr->sh_size += hdr->sh_addralign - adjust;
	    }
	}
    }

  return TRUE;
}