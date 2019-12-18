#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct bfd_link_info {scalar_t__ shared; } ;
typedef  int flagword ;
typedef  void* bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_6__ {scalar_t__ size; } ;
typedef  TYPE_1__ asection ;
struct TYPE_7__ {void* got_needed; void* dynamic_sections_needed; int /*<<< orphan*/ * dynobj; void* dynamic_sections_created; } ;

/* Variables and functions */
 scalar_t__ BYTES_IN_WORD ; 
 void* FALSE ; 
 int SEC_ALLOC ; 
 int SEC_CODE ; 
 int SEC_HAS_CONTENTS ; 
 int SEC_IN_MEMORY ; 
 int SEC_LINKER_CREATED ; 
 int SEC_LOAD ; 
 int SEC_READONLY ; 
 void* TRUE ; 
 TYPE_1__* bfd_get_section_by_name (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* bfd_make_section_with_flags (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  bfd_set_section_alignment (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 TYPE_2__* sunos_hash_table (struct bfd_link_info*) ; 

__attribute__((used)) static bfd_boolean
sunos_create_dynamic_sections (bfd *abfd,
			       struct bfd_link_info *info,
			       bfd_boolean needed)
{
  asection *s;

  if (! sunos_hash_table (info)->dynamic_sections_created)
    {
      flagword flags;

      sunos_hash_table (info)->dynobj = abfd;

      flags = (SEC_ALLOC | SEC_LOAD | SEC_HAS_CONTENTS | SEC_IN_MEMORY
	       | SEC_LINKER_CREATED);

      /* The .dynamic section holds the basic dynamic information: the
	 sun4_dynamic structure, the dynamic debugger information, and
	 the sun4_dynamic_link structure.  */
      s = bfd_make_section_with_flags (abfd, ".dynamic", flags);
      if (s == NULL
	  || ! bfd_set_section_alignment (abfd, s, 2))
	return FALSE;

      /* The .got section holds the global offset table.  The address
	 is put in the ld_got field.  */
      s = bfd_make_section_with_flags (abfd, ".got", flags);
      if (s == NULL
	  || ! bfd_set_section_alignment (abfd, s, 2))
	return FALSE;

      /* The .plt section holds the procedure linkage table.  The
	 address is put in the ld_plt field.  */
      s = bfd_make_section_with_flags (abfd, ".plt", flags | SEC_CODE);
      if (s == NULL
	  || ! bfd_set_section_alignment (abfd, s, 2))
	return FALSE;

      /* The .dynrel section holds the dynamic relocs.  The address is
	 put in the ld_rel field.  */
      s = bfd_make_section_with_flags (abfd, ".dynrel", flags | SEC_READONLY);
      if (s == NULL
	  || ! bfd_set_section_alignment (abfd, s, 2))
	return FALSE;

      /* The .hash section holds the dynamic hash table.  The address
	 is put in the ld_hash field.  */
      s = bfd_make_section_with_flags (abfd, ".hash", flags | SEC_READONLY);
      if (s == NULL
	  || ! bfd_set_section_alignment (abfd, s, 2))
	return FALSE;

      /* The .dynsym section holds the dynamic symbols.  The address
	 is put in the ld_stab field.  */
      s = bfd_make_section_with_flags (abfd, ".dynsym", flags | SEC_READONLY);
      if (s == NULL
	  || ! bfd_set_section_alignment (abfd, s, 2))
	return FALSE;

      /* The .dynstr section holds the dynamic symbol string table.
	 The address is put in the ld_symbols field.  */
      s = bfd_make_section_with_flags (abfd, ".dynstr", flags | SEC_READONLY);
      if (s == NULL
	  || ! bfd_set_section_alignment (abfd, s, 2))
	return FALSE;

      sunos_hash_table (info)->dynamic_sections_created = TRUE;
    }

  if ((needed && ! sunos_hash_table (info)->dynamic_sections_needed)
      || info->shared)
    {
      bfd *dynobj;

      dynobj = sunos_hash_table (info)->dynobj;

      s = bfd_get_section_by_name (dynobj, ".got");
      if (s->size == 0)
	s->size = BYTES_IN_WORD;

      sunos_hash_table (info)->dynamic_sections_needed = TRUE;
      sunos_hash_table (info)->got_needed = TRUE;
    }

  return TRUE;
}