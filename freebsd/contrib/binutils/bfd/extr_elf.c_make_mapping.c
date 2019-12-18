#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct elf_segment_map {unsigned int count; int includes_filehdr; int includes_phdrs; int /*<<< orphan*/ ** sections; int /*<<< orphan*/  p_type; int /*<<< orphan*/ * next; } ;
typedef  unsigned int bfd_size_type ;
typedef  scalar_t__ bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 int /*<<< orphan*/  PT_LOAD ; 
 struct elf_segment_map* bfd_zalloc (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static struct elf_segment_map *
make_mapping (bfd *abfd,
	      asection **sections,
	      unsigned int from,
	      unsigned int to,
	      bfd_boolean phdr)
{
  struct elf_segment_map *m;
  unsigned int i;
  asection **hdrpp;
  bfd_size_type amt;

  amt = sizeof (struct elf_segment_map);
  amt += (to - from - 1) * sizeof (asection *);
  m = bfd_zalloc (abfd, amt);
  if (m == NULL)
    return NULL;
  m->next = NULL;
  m->p_type = PT_LOAD;
  for (i = from, hdrpp = sections + from; i < to; i++, hdrpp++)
    m->sections[i - from] = *hdrpp;
  m->count = to - from;

  if (from == 0 && phdr)
    {
      /* Include the headers in the first PT_LOAD segment.  */
      m->includes_filehdr = 1;
      m->includes_phdrs = 1;
    }

  return m;
}