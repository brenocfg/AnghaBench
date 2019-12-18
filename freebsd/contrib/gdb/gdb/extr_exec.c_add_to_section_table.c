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
struct section_table {scalar_t__ addr; scalar_t__ endaddr; struct bfd_section* the_bfd_section; int /*<<< orphan*/ * bfd; } ;
struct bfd_section {int dummy; } ;
typedef  int flagword ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int SEC_ALLOC ; 
 int bfd_get_section_flags (int /*<<< orphan*/ *,struct bfd_section*) ; 
 scalar_t__ bfd_section_size (int /*<<< orphan*/ *,struct bfd_section*) ; 
 scalar_t__ bfd_section_vma (int /*<<< orphan*/ *,struct bfd_section*) ; 

__attribute__((used)) static void
add_to_section_table (bfd *abfd, struct bfd_section *asect,
		      void *table_pp_char)
{
  struct section_table **table_pp = (struct section_table **) table_pp_char;
  flagword aflag;

  aflag = bfd_get_section_flags (abfd, asect);
  if (!(aflag & SEC_ALLOC))
    return;
  if (0 == bfd_section_size (abfd, asect))
    return;
  (*table_pp)->bfd = abfd;
  (*table_pp)->the_bfd_section = asect;
  (*table_pp)->addr = bfd_section_vma (abfd, asect);
  (*table_pp)->endaddr = (*table_pp)->addr + bfd_section_size (abfd, asect);
  (*table_pp)++;
}