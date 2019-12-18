#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mips_elf_link_hash_table {int plt_header_size; int plt_entry_size; int /*<<< orphan*/  srelplt2; int /*<<< orphan*/ * splt; int /*<<< orphan*/ * srelplt; int /*<<< orphan*/ * srelbss; int /*<<< orphan*/ * sdynbss; scalar_t__ is_vxworks; int /*<<< orphan*/  use_rld_obj_head; } ;
struct elf_link_hash_entry {int def_regular; void* type; scalar_t__ non_elf; } ;
struct bfd_link_info {scalar_t__ shared; } ;
struct bfd_link_hash_entry {int dummy; } ;
typedef  int flagword ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_2__ {int /*<<< orphan*/  collect; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BFD_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BSF_GLOBAL ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IRIX_COMPAT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MIPS_ELF_LOG_FILE_ALIGN (int /*<<< orphan*/ *) ; 
 char* MIPS_ELF_STUB_SECTION_NAME (int /*<<< orphan*/ *) ; 
 int SEC_ALLOC ; 
 int SEC_CODE ; 
 int SEC_HAS_CONTENTS ; 
 int SEC_IN_MEMORY ; 
 int SEC_LINKER_CREATED ; 
 int SEC_LOAD ; 
 int SEC_READONLY ; 
 scalar_t__ SGI_COMPAT (int /*<<< orphan*/ *) ; 
 void* STT_OBJECT ; 
 void* STT_SECTION ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _bfd_elf_create_dynamic_sections (int /*<<< orphan*/ *,struct bfd_link_info*) ; 
 int /*<<< orphan*/  _bfd_generic_link_add_one_symbol (struct bfd_link_info*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bfd_link_hash_entry**) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/ * bfd_abs_section_ptr ; 
 int /*<<< orphan*/  bfd_elf_link_record_dynamic_symbol (struct bfd_link_info*,struct elf_link_hash_entry*) ; 
 int /*<<< orphan*/ * bfd_get_section_by_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * bfd_make_section_with_flags (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  bfd_set_section_alignment (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_section_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * bfd_und_section_ptr ; 
 int /*<<< orphan*/  elf_vxworks_create_dynamic_sections (int /*<<< orphan*/ *,struct bfd_link_info*,int /*<<< orphan*/ *) ; 
 TYPE_1__* get_elf_backend_data (int /*<<< orphan*/ *) ; 
 scalar_t__ ict_irix5 ; 
 scalar_t__ ict_none ; 
 int /*<<< orphan*/  mips_elf_create_compact_rel_section (int /*<<< orphan*/ *,struct bfd_link_info*) ; 
 int /*<<< orphan*/  mips_elf_create_got_section (int /*<<< orphan*/ *,struct bfd_link_info*,int /*<<< orphan*/ ) ; 
 char** mips_elf_dynsym_rtproc_names ; 
 struct mips_elf_link_hash_table* mips_elf_hash_table (struct bfd_link_info*) ; 
 int /*<<< orphan*/  mips_elf_rel_dyn_section (struct bfd_link_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_vxworks_exec_plt0_entry ; 
 int /*<<< orphan*/  mips_vxworks_exec_plt_entry ; 
 int /*<<< orphan*/  mips_vxworks_shared_plt0_entry ; 
 int /*<<< orphan*/  mips_vxworks_shared_plt_entry ; 

bfd_boolean
_bfd_mips_elf_create_dynamic_sections (bfd *abfd, struct bfd_link_info *info)
{
  struct elf_link_hash_entry *h;
  struct bfd_link_hash_entry *bh;
  flagword flags;
  register asection *s;
  const char * const *namep;
  struct mips_elf_link_hash_table *htab;

  htab = mips_elf_hash_table (info);
  flags = (SEC_ALLOC | SEC_LOAD | SEC_HAS_CONTENTS | SEC_IN_MEMORY
	   | SEC_LINKER_CREATED | SEC_READONLY);

  /* The psABI requires a read-only .dynamic section, but the VxWorks
     EABI doesn't.  */
  if (!htab->is_vxworks)
    {
      s = bfd_get_section_by_name (abfd, ".dynamic");
      if (s != NULL)
	{
	  if (! bfd_set_section_flags (abfd, s, flags))
	    return FALSE;
	}
    }

  /* We need to create .got section.  */
  if (! mips_elf_create_got_section (abfd, info, FALSE))
    return FALSE;

  if (! mips_elf_rel_dyn_section (info, TRUE))
    return FALSE;

  /* Create .stub section.  */
  if (bfd_get_section_by_name (abfd,
			       MIPS_ELF_STUB_SECTION_NAME (abfd)) == NULL)
    {
      s = bfd_make_section_with_flags (abfd,
				       MIPS_ELF_STUB_SECTION_NAME (abfd),
				       flags | SEC_CODE);
      if (s == NULL
	  || ! bfd_set_section_alignment (abfd, s,
					  MIPS_ELF_LOG_FILE_ALIGN (abfd)))
	return FALSE;
    }

  if ((IRIX_COMPAT (abfd) == ict_irix5 || IRIX_COMPAT (abfd) == ict_none)
      && !info->shared
      && bfd_get_section_by_name (abfd, ".rld_map") == NULL)
    {
      s = bfd_make_section_with_flags (abfd, ".rld_map",
				       flags &~ (flagword) SEC_READONLY);
      if (s == NULL
	  || ! bfd_set_section_alignment (abfd, s,
					  MIPS_ELF_LOG_FILE_ALIGN (abfd)))
	return FALSE;
    }

  /* On IRIX5, we adjust add some additional symbols and change the
     alignments of several sections.  There is no ABI documentation
     indicating that this is necessary on IRIX6, nor any evidence that
     the linker takes such action.  */
  if (IRIX_COMPAT (abfd) == ict_irix5)
    {
      for (namep = mips_elf_dynsym_rtproc_names; *namep != NULL; namep++)
	{
	  bh = NULL;
	  if (! (_bfd_generic_link_add_one_symbol
		 (info, abfd, *namep, BSF_GLOBAL, bfd_und_section_ptr, 0,
		  NULL, FALSE, get_elf_backend_data (abfd)->collect, &bh)))
	    return FALSE;

	  h = (struct elf_link_hash_entry *) bh;
	  h->non_elf = 0;
	  h->def_regular = 1;
	  h->type = STT_SECTION;

	  if (! bfd_elf_link_record_dynamic_symbol (info, h))
	    return FALSE;
	}

      /* We need to create a .compact_rel section.  */
      if (SGI_COMPAT (abfd))
	{
	  if (!mips_elf_create_compact_rel_section (abfd, info))
	    return FALSE;
	}

      /* Change alignments of some sections.  */
      s = bfd_get_section_by_name (abfd, ".hash");
      if (s != NULL)
	bfd_set_section_alignment (abfd, s, MIPS_ELF_LOG_FILE_ALIGN (abfd));
      s = bfd_get_section_by_name (abfd, ".dynsym");
      if (s != NULL)
	bfd_set_section_alignment (abfd, s, MIPS_ELF_LOG_FILE_ALIGN (abfd));
      s = bfd_get_section_by_name (abfd, ".dynstr");
      if (s != NULL)
	bfd_set_section_alignment (abfd, s, MIPS_ELF_LOG_FILE_ALIGN (abfd));
      s = bfd_get_section_by_name (abfd, ".reginfo");
      if (s != NULL)
	bfd_set_section_alignment (abfd, s, MIPS_ELF_LOG_FILE_ALIGN (abfd));
      s = bfd_get_section_by_name (abfd, ".dynamic");
      if (s != NULL)
	bfd_set_section_alignment (abfd, s, MIPS_ELF_LOG_FILE_ALIGN (abfd));
    }

  if (!info->shared)
    {
      const char *name;

      name = SGI_COMPAT (abfd) ? "_DYNAMIC_LINK" : "_DYNAMIC_LINKING";
      bh = NULL;
      if (!(_bfd_generic_link_add_one_symbol
	    (info, abfd, name, BSF_GLOBAL, bfd_abs_section_ptr, 0,
	     NULL, FALSE, get_elf_backend_data (abfd)->collect, &bh)))
	return FALSE;

      h = (struct elf_link_hash_entry *) bh;
      h->non_elf = 0;
      h->def_regular = 1;
      h->type = STT_SECTION;

      if (! bfd_elf_link_record_dynamic_symbol (info, h))
	return FALSE;

      if (! mips_elf_hash_table (info)->use_rld_obj_head)
	{
	  /* __rld_map is a four byte word located in the .data section
	     and is filled in by the rtld to contain a pointer to
	     the _r_debug structure. Its symbol value will be set in
	     _bfd_mips_elf_finish_dynamic_symbol.  */
	  s = bfd_get_section_by_name (abfd, ".rld_map");
	  BFD_ASSERT (s != NULL);

	  name = SGI_COMPAT (abfd) ? "__rld_map" : "__RLD_MAP";
	  bh = NULL;
	  if (!(_bfd_generic_link_add_one_symbol
		(info, abfd, name, BSF_GLOBAL, s, 0, NULL, FALSE,
		 get_elf_backend_data (abfd)->collect, &bh)))
	    return FALSE;

	  h = (struct elf_link_hash_entry *) bh;
	  h->non_elf = 0;
	  h->def_regular = 1;
	  h->type = STT_OBJECT;

	  if (! bfd_elf_link_record_dynamic_symbol (info, h))
	    return FALSE;
	}
    }

  if (htab->is_vxworks)
    {
      /* Create the .plt, .rela.plt, .dynbss and .rela.bss sections.
	 Also create the _PROCEDURE_LINKAGE_TABLE symbol.  */
      if (!_bfd_elf_create_dynamic_sections (abfd, info))
	return FALSE;

      /* Cache the sections created above.  */
      htab->sdynbss = bfd_get_section_by_name (abfd, ".dynbss");
      htab->srelbss = bfd_get_section_by_name (abfd, ".rela.bss");
      htab->srelplt = bfd_get_section_by_name (abfd, ".rela.plt");
      htab->splt = bfd_get_section_by_name (abfd, ".plt");
      if (!htab->sdynbss
	  || (!htab->srelbss && !info->shared)
	  || !htab->srelplt
	  || !htab->splt)
	abort ();

      /* Do the usual VxWorks handling.  */
      if (!elf_vxworks_create_dynamic_sections (abfd, info, &htab->srelplt2))
	return FALSE;

      /* Work out the PLT sizes.  */
      if (info->shared)
	{
	  htab->plt_header_size
	    = 4 * ARRAY_SIZE (mips_vxworks_shared_plt0_entry);
	  htab->plt_entry_size
	    = 4 * ARRAY_SIZE (mips_vxworks_shared_plt_entry);
	}
      else
	{
	  htab->plt_header_size
	    = 4 * ARRAY_SIZE (mips_vxworks_exec_plt0_entry);
	  htab->plt_entry_size
	    = 4 * ARRAY_SIZE (mips_vxworks_exec_plt_entry);
	}
    }

  return TRUE;
}