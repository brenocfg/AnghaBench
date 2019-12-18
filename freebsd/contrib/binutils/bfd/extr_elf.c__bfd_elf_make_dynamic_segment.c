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
struct elf_segment_map {int count; int /*<<< orphan*/ ** sections; int /*<<< orphan*/  p_type; int /*<<< orphan*/ * next; } ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 int /*<<< orphan*/  PT_DYNAMIC ; 
 struct elf_segment_map* bfd_zalloc (int /*<<< orphan*/ *,int) ; 

struct elf_segment_map *
_bfd_elf_make_dynamic_segment (bfd *abfd, asection *dynsec)
{
  struct elf_segment_map *m;

  m = bfd_zalloc (abfd, sizeof (struct elf_segment_map));
  if (m == NULL)
    return NULL;
  m->next = NULL;
  m->p_type = PT_DYNAMIC;
  m->count = 1;
  m->sections[0] = dynsec;

  return m;
}