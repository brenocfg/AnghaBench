#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int flagword ;
typedef  int /*<<< orphan*/  elf_gp ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_13__ {int /*<<< orphan*/  ri_gp_value; } ;
struct TYPE_12__ {int /*<<< orphan*/  ri_gp_value; } ;
struct TYPE_11__ {int size; scalar_t__ kind; } ;
struct TYPE_10__ {int sh_type; int sh_size; int /*<<< orphan*/  bfd_section; } ;
typedef  TYPE_1__ Elf_Internal_Shdr ;
typedef  TYPE_2__ Elf_Internal_Options ;
typedef  int /*<<< orphan*/  Elf_External_Options ;
typedef  TYPE_3__ Elf64_Internal_RegInfo ;
typedef  int /*<<< orphan*/  Elf64_External_RegInfo ;
typedef  TYPE_4__ Elf32_RegInfo ;
typedef  int /*<<< orphan*/  Elf32_External_RegInfo ;

/* Variables and functions */
 scalar_t__ ABI_64_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CONST_STRNEQ (char const*,char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MIPS_ELF_OPTIONS_SECTION_NAME (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MIPS_ELF_OPTIONS_SECTION_NAME_P (char const*) ; 
 scalar_t__ ODK_REGINFO ; 
 int SEC_DEBUGGING ; 
 int SEC_LINK_DUPLICATES_SAME_SIZE ; 
 int SEC_LINK_ONCE ; 
#define  SHT_MIPS_CONFLICT 140 
#define  SHT_MIPS_CONTENT 139 
#define  SHT_MIPS_DEBUG 138 
#define  SHT_MIPS_DWARF 137 
#define  SHT_MIPS_EVENTS 136 
#define  SHT_MIPS_GPTAB 135 
#define  SHT_MIPS_IFACE 134 
#define  SHT_MIPS_LIBLIST 133 
#define  SHT_MIPS_MSYM 132 
#define  SHT_MIPS_OPTIONS 131 
#define  SHT_MIPS_REGINFO 130 
#define  SHT_MIPS_SYMBOL_LIB 129 
#define  SHT_MIPS_UCODE 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_elf_make_section_from_shdr (int /*<<< orphan*/ *,TYPE_1__*,char const*,int) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfd_get_section_contents (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int bfd_get_section_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bfd_malloc (int) ; 
 int /*<<< orphan*/  bfd_mips_elf32_swap_reginfo_in (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  bfd_mips_elf64_swap_reginfo_in (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  bfd_mips_elf_swap_options_in (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  bfd_set_section_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

bfd_boolean
_bfd_mips_elf_section_from_shdr (bfd *abfd,
				 Elf_Internal_Shdr *hdr,
				 const char *name,
				 int shindex)
{
  flagword flags = 0;

  /* There ought to be a place to keep ELF backend specific flags, but
     at the moment there isn't one.  We just keep track of the
     sections by their name, instead.  Fortunately, the ABI gives
     suggested names for all the MIPS specific sections, so we will
     probably get away with this.  */
  switch (hdr->sh_type)
    {
    case SHT_MIPS_LIBLIST:
      if (strcmp (name, ".liblist") != 0)
	return FALSE;
      break;
    case SHT_MIPS_MSYM:
      if (strcmp (name, ".msym") != 0)
	return FALSE;
      break;
    case SHT_MIPS_CONFLICT:
      if (strcmp (name, ".conflict") != 0)
	return FALSE;
      break;
    case SHT_MIPS_GPTAB:
      if (! CONST_STRNEQ (name, ".gptab."))
	return FALSE;
      break;
    case SHT_MIPS_UCODE:
      if (strcmp (name, ".ucode") != 0)
	return FALSE;
      break;
    case SHT_MIPS_DEBUG:
      if (strcmp (name, ".mdebug") != 0)
	return FALSE;
      flags = SEC_DEBUGGING;
      break;
    case SHT_MIPS_REGINFO:
      if (strcmp (name, ".reginfo") != 0
	  || hdr->sh_size != sizeof (Elf32_External_RegInfo))
	return FALSE;
      flags = (SEC_LINK_ONCE | SEC_LINK_DUPLICATES_SAME_SIZE);
      break;
    case SHT_MIPS_IFACE:
      if (strcmp (name, ".MIPS.interfaces") != 0)
	return FALSE;
      break;
    case SHT_MIPS_CONTENT:
      if (! CONST_STRNEQ (name, ".MIPS.content"))
	return FALSE;
      break;
    case SHT_MIPS_OPTIONS:
      if (!MIPS_ELF_OPTIONS_SECTION_NAME_P (name))
	return FALSE;
      break;
    case SHT_MIPS_DWARF:
      if (! CONST_STRNEQ (name, ".debug_"))
	return FALSE;
      break;
    case SHT_MIPS_SYMBOL_LIB:
      if (strcmp (name, ".MIPS.symlib") != 0)
	return FALSE;
      break;
    case SHT_MIPS_EVENTS:
      if (! CONST_STRNEQ (name, ".MIPS.events")
	  && ! CONST_STRNEQ (name, ".MIPS.post_rel"))
	return FALSE;
      break;
    default:
      break;
    }

  if (! _bfd_elf_make_section_from_shdr (abfd, hdr, name, shindex))
    return FALSE;

  if (flags)
    {
      if (! bfd_set_section_flags (abfd, hdr->bfd_section,
				   (bfd_get_section_flags (abfd,
							   hdr->bfd_section)
				    | flags)))
	return FALSE;
    }

  /* FIXME: We should record sh_info for a .gptab section.  */

  /* For a .reginfo section, set the gp value in the tdata information
     from the contents of this section.  We need the gp value while
     processing relocs, so we just get it now.  The .reginfo section
     is not used in the 64-bit MIPS ELF ABI.  */
  if (hdr->sh_type == SHT_MIPS_REGINFO)
    {
      Elf32_External_RegInfo ext;
      Elf32_RegInfo s;

      if (! bfd_get_section_contents (abfd, hdr->bfd_section,
				      &ext, 0, sizeof ext))
	return FALSE;
      bfd_mips_elf32_swap_reginfo_in (abfd, &ext, &s);
      elf_gp (abfd) = s.ri_gp_value;
    }

  /* For a SHT_MIPS_OPTIONS section, look for a ODK_REGINFO entry, and
     set the gp value based on what we find.  We may see both
     SHT_MIPS_REGINFO and SHT_MIPS_OPTIONS/ODK_REGINFO; in that case,
     they should agree.  */
  if (hdr->sh_type == SHT_MIPS_OPTIONS)
    {
      bfd_byte *contents, *l, *lend;

      contents = bfd_malloc (hdr->sh_size);
      if (contents == NULL)
	return FALSE;
      if (! bfd_get_section_contents (abfd, hdr->bfd_section, contents,
				      0, hdr->sh_size))
	{
	  free (contents);
	  return FALSE;
	}
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
	      Elf64_Internal_RegInfo intreg;

	      bfd_mips_elf64_swap_reginfo_in
		(abfd,
		 ((Elf64_External_RegInfo *)
		  (l + sizeof (Elf_External_Options))),
		 &intreg);
	      elf_gp (abfd) = intreg.ri_gp_value;
	    }
	  else if (intopt.kind == ODK_REGINFO)
	    {
	      Elf32_RegInfo intreg;

	      bfd_mips_elf32_swap_reginfo_in
		(abfd,
		 ((Elf32_External_RegInfo *)
		  (l + sizeof (Elf_External_Options))),
		 &intreg);
	      elf_gp (abfd) = intreg.ri_gp_value;
	    }
	  l += intopt.size;
	}
      free (contents);
    }

  return TRUE;
}