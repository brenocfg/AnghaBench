#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_3__ {scalar_t__ size; int /*<<< orphan*/  reloc_count; } ;
typedef  TYPE_1__ asection ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 unsigned int SCORE_ELF_REL_SIZE (int /*<<< orphan*/ *) ; 
 TYPE_1__* score_elf_rel_dyn_section (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
score_elf_allocate_dynamic_relocations (bfd *abfd, unsigned int n)
{
  asection *s;

  s = score_elf_rel_dyn_section (abfd, FALSE);
  BFD_ASSERT (s != NULL);

  if (s->size == 0)
    {
      /* Make room for a null element.  */
      s->size += SCORE_ELF_REL_SIZE (abfd);
      ++s->reloc_count;
    }
  s->size += n * SCORE_ELF_REL_SIZE (abfd);
}