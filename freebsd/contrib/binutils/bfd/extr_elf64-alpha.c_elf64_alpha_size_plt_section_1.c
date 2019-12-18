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
struct TYPE_3__ {void* needs_plt; } ;
struct alpha_elf_link_hash_entry {TYPE_1__ root; struct alpha_elf_got_entry* got_entries; } ;
struct alpha_elf_got_entry {scalar_t__ reloc_type; scalar_t__ use_count; scalar_t__ plt_offset; struct alpha_elf_got_entry* next; } ;
typedef  void* bfd_boolean ;
struct TYPE_4__ {scalar_t__ size; } ;
typedef  TYPE_2__ asection ;
typedef  scalar_t__ PTR ;

/* Variables and functions */
 void* FALSE ; 
 scalar_t__ PLT_ENTRY_SIZE ; 
 scalar_t__ PLT_HEADER_SIZE ; 
 scalar_t__ R_ALPHA_LITERAL ; 
 void* TRUE ; 

__attribute__((used)) static bfd_boolean
elf64_alpha_size_plt_section_1 (struct alpha_elf_link_hash_entry *h, PTR data)
{
  asection *splt = (asection *) data;
  struct alpha_elf_got_entry *gotent;
  bfd_boolean saw_one = FALSE;

  /* If we didn't need an entry before, we still don't.  */
  if (!h->root.needs_plt)
    return TRUE;

  /* For each LITERAL got entry still in use, allocate a plt entry.  */
  for (gotent = h->got_entries; gotent ; gotent = gotent->next)
    if (gotent->reloc_type == R_ALPHA_LITERAL
	&& gotent->use_count > 0)
      {
	if (splt->size == 0)
	  splt->size = PLT_HEADER_SIZE;
	gotent->plt_offset = splt->size;
	splt->size += PLT_ENTRY_SIZE;
	saw_one = TRUE;
      }

  /* If there weren't any, there's no longer a need for the PLT entry.  */
  if (!saw_one)
    h->root.needs_plt = FALSE;

  return TRUE;
}