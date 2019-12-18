#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_10__ {int flags; } ;
typedef  TYPE_1__ bfd ;
struct TYPE_11__ {int size; } ;
typedef  TYPE_2__ asection ;
struct TYPE_12__ {int sh_info; int sh_entsize; int /*<<< orphan*/  sh_flags; int /*<<< orphan*/  sh_type; } ;
typedef  TYPE_3__ Elf_Internal_Shdr ;
typedef  int /*<<< orphan*/  Elf32_Lib ;
typedef  int /*<<< orphan*/  Elf32_External_gptab ;
typedef  int /*<<< orphan*/  Elf32_External_RegInfo ;

/* Variables and functions */
 scalar_t__ CONST_STRNEQ (char const*,char*) ; 
 int DYNAMIC ; 
 scalar_t__ MIPS_ELF_OPTIONS_SECTION_NAME_P (char const*) ; 
 scalar_t__ SGI_COMPAT (TYPE_1__*) ; 
 int /*<<< orphan*/  SHF_ALLOC ; 
 int /*<<< orphan*/  SHF_MIPS_GPREL ; 
 int /*<<< orphan*/  SHF_MIPS_NOSTRIP ; 
 int /*<<< orphan*/  SHT_MIPS_CONFLICT ; 
 int /*<<< orphan*/  SHT_MIPS_CONTENT ; 
 int /*<<< orphan*/  SHT_MIPS_DEBUG ; 
 int /*<<< orphan*/  SHT_MIPS_DWARF ; 
 int /*<<< orphan*/  SHT_MIPS_EVENTS ; 
 int /*<<< orphan*/  SHT_MIPS_GPTAB ; 
 int /*<<< orphan*/  SHT_MIPS_IFACE ; 
 int /*<<< orphan*/  SHT_MIPS_LIBLIST ; 
 int /*<<< orphan*/  SHT_MIPS_MSYM ; 
 int /*<<< orphan*/  SHT_MIPS_OPTIONS ; 
 int /*<<< orphan*/  SHT_MIPS_REGINFO ; 
 int /*<<< orphan*/  SHT_MIPS_SYMBOL_LIB ; 
 int /*<<< orphan*/  SHT_MIPS_UCODE ; 
 int SIZEOF_MIPS_DYNSYM_SECNAMES ; 
 int /*<<< orphan*/  TRUE ; 
 char* bfd_get_section_name (TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

bfd_boolean
_bfd_mips_elf_fake_sections (bfd *abfd, Elf_Internal_Shdr *hdr, asection *sec)
{
  const char *name = bfd_get_section_name (abfd, sec);

  if (strcmp (name, ".liblist") == 0)
    {
      hdr->sh_type = SHT_MIPS_LIBLIST;
      hdr->sh_info = sec->size / sizeof (Elf32_Lib);
      /* The sh_link field is set in final_write_processing.  */
    }
  else if (strcmp (name, ".conflict") == 0)
    hdr->sh_type = SHT_MIPS_CONFLICT;
  else if (CONST_STRNEQ (name, ".gptab."))
    {
      hdr->sh_type = SHT_MIPS_GPTAB;
      hdr->sh_entsize = sizeof (Elf32_External_gptab);
      /* The sh_info field is set in final_write_processing.  */
    }
  else if (strcmp (name, ".ucode") == 0)
    hdr->sh_type = SHT_MIPS_UCODE;
  else if (strcmp (name, ".mdebug") == 0)
    {
      hdr->sh_type = SHT_MIPS_DEBUG;
      /* In a shared object on IRIX 5.3, the .mdebug section has an
         entsize of 0.  FIXME: Does this matter?  */
      if (SGI_COMPAT (abfd) && (abfd->flags & DYNAMIC) != 0)
	hdr->sh_entsize = 0;
      else
	hdr->sh_entsize = 1;
    }
  else if (strcmp (name, ".reginfo") == 0)
    {
      hdr->sh_type = SHT_MIPS_REGINFO;
      /* In a shared object on IRIX 5.3, the .reginfo section has an
         entsize of 0x18.  FIXME: Does this matter?  */
      if (SGI_COMPAT (abfd))
	{
	  if ((abfd->flags & DYNAMIC) != 0)
	    hdr->sh_entsize = sizeof (Elf32_External_RegInfo);
	  else
	    hdr->sh_entsize = 1;
	}
      else
	hdr->sh_entsize = sizeof (Elf32_External_RegInfo);
    }
  else if (SGI_COMPAT (abfd)
	   && (strcmp (name, ".hash") == 0
	       || strcmp (name, ".dynamic") == 0
	       || strcmp (name, ".dynstr") == 0))
    {
      if (SGI_COMPAT (abfd))
	hdr->sh_entsize = 0;
#if 0
      /* This isn't how the IRIX6 linker behaves.  */
      hdr->sh_info = SIZEOF_MIPS_DYNSYM_SECNAMES;
#endif
    }
  else if (strcmp (name, ".got") == 0
	   || strcmp (name, ".srdata") == 0
	   || strcmp (name, ".sdata") == 0
	   || strcmp (name, ".sbss") == 0
	   || strcmp (name, ".lit4") == 0
	   || strcmp (name, ".lit8") == 0)
    hdr->sh_flags |= SHF_MIPS_GPREL;
  else if (strcmp (name, ".MIPS.interfaces") == 0)
    {
      hdr->sh_type = SHT_MIPS_IFACE;
      hdr->sh_flags |= SHF_MIPS_NOSTRIP;
    }
  else if (CONST_STRNEQ (name, ".MIPS.content"))
    {
      hdr->sh_type = SHT_MIPS_CONTENT;
      hdr->sh_flags |= SHF_MIPS_NOSTRIP;
      /* The sh_info field is set in final_write_processing.  */
    }
  else if (MIPS_ELF_OPTIONS_SECTION_NAME_P (name))
    {
      hdr->sh_type = SHT_MIPS_OPTIONS;
      hdr->sh_entsize = 1;
      hdr->sh_flags |= SHF_MIPS_NOSTRIP;
    }
  else if (CONST_STRNEQ (name, ".debug_"))
    hdr->sh_type = SHT_MIPS_DWARF;
  else if (strcmp (name, ".MIPS.symlib") == 0)
    {
      hdr->sh_type = SHT_MIPS_SYMBOL_LIB;
      /* The sh_link and sh_info fields are set in
         final_write_processing.  */
    }
  else if (CONST_STRNEQ (name, ".MIPS.events")
	   || CONST_STRNEQ (name, ".MIPS.post_rel"))
    {
      hdr->sh_type = SHT_MIPS_EVENTS;
      hdr->sh_flags |= SHF_MIPS_NOSTRIP;
      /* The sh_link field is set in final_write_processing.  */
    }
  else if (strcmp (name, ".msym") == 0)
    {
      hdr->sh_type = SHT_MIPS_MSYM;
      hdr->sh_flags |= SHF_ALLOC;
      hdr->sh_entsize = 8;
    }

  /* The generic elf_fake_sections will set up REL_HDR using the default
   kind of relocations.  We used to set up a second header for the
   non-default kind of relocations here, but only NewABI would use
   these, and the IRIX ld doesn't like resulting empty RELA sections.
   Thus we create those header only on demand now.  */

  return TRUE;
}