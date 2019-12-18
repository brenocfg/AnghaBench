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
struct section_closure {TYPE_1__* end; } ;
struct bfd_section {int dummy; } ;
struct bfd {int dummy; } ;
typedef  int flagword ;
struct TYPE_2__ {scalar_t__ addr; scalar_t__ endaddr; struct bfd_section* the_bfd_section; struct bfd* bfd; } ;

/* Variables and functions */
 int SEC_ALLOC ; 
 int bfd_get_section_flags (struct bfd*,struct bfd_section*) ; 
 scalar_t__ bfd_section_size (struct bfd*,struct bfd_section*) ; 
 scalar_t__ bfd_section_vma (struct bfd*,struct bfd_section*) ; 

__attribute__((used)) static void
add_to_section_table (struct bfd *abfd, struct bfd_section *asect,
		      void *closure)
{
  struct section_closure *pp = closure;
  flagword aflag;

  /* NOTE: cagney/2003-10-22: Is this pruning useful?  */
  aflag = bfd_get_section_flags (abfd, asect);
  if (!(aflag & SEC_ALLOC))
    return;
  if (bfd_section_size (abfd, asect) == 0)
    return;
  pp->end->bfd = abfd;
  pp->end->the_bfd_section = asect;
  pp->end->addr = bfd_section_vma (abfd, asect);
  pp->end->endaddr = pp->end->addr + bfd_section_size (abfd, asect);
  pp->end++;
}