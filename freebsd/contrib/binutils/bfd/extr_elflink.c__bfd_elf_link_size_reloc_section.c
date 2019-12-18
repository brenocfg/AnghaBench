#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct elf_link_hash_entry {int dummy; } ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_7__ {int reloc_count; } ;
typedef  TYPE_1__ asection ;
struct TYPE_8__ {int sh_size; int sh_entsize; int /*<<< orphan*/ * contents; } ;
struct TYPE_9__ {int rel_count; int rel_count2; struct elf_link_hash_entry** rel_hashes; TYPE_2__ rel_hdr; } ;
typedef  TYPE_2__ Elf_Internal_Shdr ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * bfd_zalloc (int /*<<< orphan*/ *,int) ; 
 struct elf_link_hash_entry** bfd_zmalloc (int) ; 
 TYPE_3__* elf_section_data (TYPE_1__*) ; 

bfd_boolean
_bfd_elf_link_size_reloc_section (bfd *abfd,
				  Elf_Internal_Shdr *rel_hdr,
				  asection *o)
{
  bfd_size_type reloc_count;
  bfd_size_type num_rel_hashes;

  /* Figure out how many relocations there will be.  */
  if (rel_hdr == &elf_section_data (o)->rel_hdr)
    reloc_count = elf_section_data (o)->rel_count;
  else
    reloc_count = elf_section_data (o)->rel_count2;

  num_rel_hashes = o->reloc_count;
  if (num_rel_hashes < reloc_count)
    num_rel_hashes = reloc_count;

  /* That allows us to calculate the size of the section.  */
  rel_hdr->sh_size = rel_hdr->sh_entsize * reloc_count;

  /* The contents field must last into write_object_contents, so we
     allocate it with bfd_alloc rather than malloc.  Also since we
     cannot be sure that the contents will actually be filled in,
     we zero the allocated space.  */
  rel_hdr->contents = bfd_zalloc (abfd, rel_hdr->sh_size);
  if (rel_hdr->contents == NULL && rel_hdr->sh_size != 0)
    return FALSE;

  /* We only allocate one set of hash entries, so we only do it the
     first time we are called.  */
  if (elf_section_data (o)->rel_hashes == NULL
      && num_rel_hashes)
    {
      struct elf_link_hash_entry **p;

      p = bfd_zmalloc (num_rel_hashes * sizeof (struct elf_link_hash_entry *));
      if (p == NULL)
	return FALSE;

      elf_section_data (o)->rel_hashes = p;
    }

  return TRUE;
}