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
struct elf_segment_map {unsigned long p_type; unsigned int count; struct elf_segment_map* next; int /*<<< orphan*/  sections; void* includes_phdrs; void* includes_filehdr; void* p_paddr_valid; void* p_flags_valid; int /*<<< orphan*/  p_paddr; int /*<<< orphan*/  p_flags; } ;
typedef  int /*<<< orphan*/  flagword ;
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int bfd_size_type ;
typedef  void* bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_2__ {struct elf_segment_map* segment_map; } ;

/* Variables and functions */
 void* FALSE ; 
 void* TRUE ; 
 scalar_t__ bfd_get_flavour (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_target_elf_flavour ; 
 struct elf_segment_map* bfd_zalloc (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* elf_tdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ **,unsigned int) ; 

bfd_boolean
bfd_record_phdr (bfd *abfd,
		 unsigned long type,
		 bfd_boolean flags_valid,
		 flagword flags,
		 bfd_boolean at_valid,
		 bfd_vma at,
		 bfd_boolean includes_filehdr,
		 bfd_boolean includes_phdrs,
		 unsigned int count,
		 asection **secs)
{
  struct elf_segment_map *m, **pm;
  bfd_size_type amt;

  if (bfd_get_flavour (abfd) != bfd_target_elf_flavour)
    return TRUE;

  amt = sizeof (struct elf_segment_map);
  amt += ((bfd_size_type) count - 1) * sizeof (asection *);
  m = bfd_zalloc (abfd, amt);
  if (m == NULL)
    return FALSE;

  m->p_type = type;
  m->p_flags = flags;
  m->p_paddr = at;
  m->p_flags_valid = flags_valid;
  m->p_paddr_valid = at_valid;
  m->includes_filehdr = includes_filehdr;
  m->includes_phdrs = includes_phdrs;
  m->count = count;
  if (count > 0)
    memcpy (m->sections, secs, count * sizeof (asection *));

  for (pm = &elf_tdata (abfd)->segment_map; *pm != NULL; pm = &(*pm)->next)
    ;
  *pm = m;

  return TRUE;
}