#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct elf_backend_data {int dynamic_sec_flags; int /*<<< orphan*/  (* elf_backend_create_dynamic_sections ) (int /*<<< orphan*/ *,struct bfd_link_info*) ;TYPE_1__* s; } ;
struct bfd_link_info {scalar_t__ emit_gnu_hash; scalar_t__ emit_hash; scalar_t__ executable; int /*<<< orphan*/  hash; } ;
typedef  int flagword ;
typedef  scalar_t__ bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_8__ {scalar_t__ dynamic_sections_created; int /*<<< orphan*/ * dynobj; } ;
struct TYPE_6__ {int sh_entsize; } ;
struct TYPE_7__ {TYPE_2__ this_hdr; } ;
struct TYPE_5__ {int log_file_align; int sizeof_hash_entry; int arch_size; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int SEC_READONLY ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _bfd_elf_define_linkage_sym (int /*<<< orphan*/ *,struct bfd_link_info*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  _bfd_elf_link_create_dynstrtab (int /*<<< orphan*/ *,struct bfd_link_info*) ; 
 int /*<<< orphan*/ * bfd_make_section_with_flags (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  bfd_set_section_alignment (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_4__* elf_hash_table (struct bfd_link_info*) ; 
 TYPE_3__* elf_section_data (int /*<<< orphan*/ *) ; 
 struct elf_backend_data* get_elf_backend_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_elf_hash_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct bfd_link_info*) ; 

bfd_boolean
_bfd_elf_link_create_dynamic_sections (bfd *abfd, struct bfd_link_info *info)
{
  flagword flags;
  register asection *s;
  const struct elf_backend_data *bed;

  if (! is_elf_hash_table (info->hash))
    return FALSE;

  if (elf_hash_table (info)->dynamic_sections_created)
    return TRUE;

  if (!_bfd_elf_link_create_dynstrtab (abfd, info))
    return FALSE;

  abfd = elf_hash_table (info)->dynobj;
  bed = get_elf_backend_data (abfd);

  flags = bed->dynamic_sec_flags;

  /* A dynamically linked executable has a .interp section, but a
     shared library does not.  */
  if (info->executable)
    {
      s = bfd_make_section_with_flags (abfd, ".interp",
				       flags | SEC_READONLY);
      if (s == NULL)
	return FALSE;
    }

  /* Create sections to hold version informations.  These are removed
     if they are not needed.  */
  s = bfd_make_section_with_flags (abfd, ".gnu.version_d",
				   flags | SEC_READONLY);
  if (s == NULL
      || ! bfd_set_section_alignment (abfd, s, bed->s->log_file_align))
    return FALSE;

  s = bfd_make_section_with_flags (abfd, ".gnu.version",
				   flags | SEC_READONLY);
  if (s == NULL
      || ! bfd_set_section_alignment (abfd, s, 1))
    return FALSE;

  s = bfd_make_section_with_flags (abfd, ".gnu.version_r",
				   flags | SEC_READONLY);
  if (s == NULL
      || ! bfd_set_section_alignment (abfd, s, bed->s->log_file_align))
    return FALSE;

  s = bfd_make_section_with_flags (abfd, ".dynsym",
				   flags | SEC_READONLY);
  if (s == NULL
      || ! bfd_set_section_alignment (abfd, s, bed->s->log_file_align))
    return FALSE;

  s = bfd_make_section_with_flags (abfd, ".dynstr",
				   flags | SEC_READONLY);
  if (s == NULL)
    return FALSE;

  s = bfd_make_section_with_flags (abfd, ".dynamic", flags);
  if (s == NULL
      || ! bfd_set_section_alignment (abfd, s, bed->s->log_file_align))
    return FALSE;

  /* The special symbol _DYNAMIC is always set to the start of the
     .dynamic section.  We could set _DYNAMIC in a linker script, but we
     only want to define it if we are, in fact, creating a .dynamic
     section.  We don't want to define it if there is no .dynamic
     section, since on some ELF platforms the start up code examines it
     to decide how to initialize the process.  */
  if (!_bfd_elf_define_linkage_sym (abfd, info, s, "_DYNAMIC"))
    return FALSE;

  if (info->emit_hash)
    {
      s = bfd_make_section_with_flags (abfd, ".hash", flags | SEC_READONLY);
      if (s == NULL
	  || ! bfd_set_section_alignment (abfd, s, bed->s->log_file_align))
	return FALSE;
      elf_section_data (s)->this_hdr.sh_entsize = bed->s->sizeof_hash_entry;
    }

  if (info->emit_gnu_hash)
    {
      s = bfd_make_section_with_flags (abfd, ".gnu.hash",
				       flags | SEC_READONLY);
      if (s == NULL
	  || ! bfd_set_section_alignment (abfd, s, bed->s->log_file_align))
	return FALSE;
      /* For 64-bit ELF, .gnu.hash is a non-uniform entity size section:
	 4 32-bit words followed by variable count of 64-bit words, then
	 variable count of 32-bit words.  */
      if (bed->s->arch_size == 64)
	elf_section_data (s)->this_hdr.sh_entsize = 0;
      else
	elf_section_data (s)->this_hdr.sh_entsize = 4;
    }

  /* Let the backend create the rest of the sections.  This lets the
     backend set the right flags.  The backend will normally create
     the .got and .plt sections.  */
  if (! (*bed->elf_backend_create_dynamic_sections) (abfd, info))
    return FALSE;

  elf_hash_table (info)->dynamic_sections_created = TRUE;

  return TRUE;
}