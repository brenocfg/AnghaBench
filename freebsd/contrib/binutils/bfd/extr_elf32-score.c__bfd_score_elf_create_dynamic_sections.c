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
struct elf_link_hash_entry {int def_regular; int /*<<< orphan*/  type; scalar_t__ non_elf; } ;
struct bfd_link_info {int /*<<< orphan*/  shared; } ;
struct bfd_link_hash_entry {int dummy; } ;
typedef  int flagword ;
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_4__ {int /*<<< orphan*/  dynobj; } ;
struct TYPE_3__ {int /*<<< orphan*/  collect; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSF_GLOBAL ; 
 int /*<<< orphan*/  FALSE ; 
 char* SCORE_ELF_STUB_SECTION_NAME ; 
 int SEC_ALLOC ; 
 int SEC_CODE ; 
 int SEC_HAS_CONTENTS ; 
 int SEC_IN_MEMORY ; 
 int SEC_LINKER_CREATED ; 
 int SEC_LOAD ; 
 int SEC_READONLY ; 
 int /*<<< orphan*/  STT_SECTION ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _bfd_generic_link_add_one_symbol (struct bfd_link_info*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bfd_link_hash_entry**) ; 
 int /*<<< orphan*/  bfd_abs_section_ptr ; 
 int /*<<< orphan*/  bfd_elf_link_record_dynamic_symbol (struct bfd_link_info*,struct elf_link_hash_entry*) ; 
 int /*<<< orphan*/ * bfd_get_section_by_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * bfd_make_section_with_flags (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  bfd_set_section_alignment (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bfd_set_section_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_2__* elf_hash_table (struct bfd_link_info*) ; 
 TYPE_1__* get_elf_backend_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  score_elf_create_got_section (int /*<<< orphan*/ *,struct bfd_link_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  score_elf_rel_dyn_section (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_boolean
_bfd_score_elf_create_dynamic_sections (bfd *abfd, struct bfd_link_info *info)
{
  struct elf_link_hash_entry *h;
  struct bfd_link_hash_entry *bh;
  flagword flags;
  asection *s;

  flags = (SEC_ALLOC | SEC_LOAD | SEC_HAS_CONTENTS | SEC_IN_MEMORY
           | SEC_LINKER_CREATED | SEC_READONLY);

  /* ABI requests the .dynamic section to be read only.  */
  s = bfd_get_section_by_name (abfd, ".dynamic");
  if (s != NULL)
    {
      if (!bfd_set_section_flags (abfd, s, flags))
        return FALSE;
    }

  /* We need to create .got section.  */
  if (!score_elf_create_got_section (abfd, info, FALSE))
    return FALSE;

  if (!score_elf_rel_dyn_section (elf_hash_table (info)->dynobj, TRUE))
    return FALSE;

  /* Create .stub section.  */
  if (bfd_get_section_by_name (abfd, SCORE_ELF_STUB_SECTION_NAME) == NULL)
    {
      s = bfd_make_section_with_flags (abfd, SCORE_ELF_STUB_SECTION_NAME,
                                       flags | SEC_CODE);
      if (s == NULL
          || !bfd_set_section_alignment (abfd, s, 2))

        return FALSE;
    }

  if (!info->shared)
    {
      const char *name;

      name = "_DYNAMIC_LINK";
      bh = NULL;
      if (!(_bfd_generic_link_add_one_symbol
            (info, abfd, name, BSF_GLOBAL, bfd_abs_section_ptr,
             (bfd_vma) 0, (const char *)NULL, FALSE, get_elf_backend_data (abfd)->collect, &bh)))
        return FALSE;

      h = (struct elf_link_hash_entry *)bh;
      h->non_elf = 0;
      h->def_regular = 1;
      h->type = STT_SECTION;

      if (!bfd_elf_link_record_dynamic_symbol (info, h))
        return FALSE;
    }

  return TRUE;
}