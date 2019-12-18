#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_4__ {int flags; } ;
typedef  TYPE_1__ asection ;

/* Variables and functions */
 int SEC_EXCLUDE ; 
 TYPE_1__* bfd_get_section_by_name (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static asection *
score_elf_got_section (bfd *abfd, bfd_boolean maybe_excluded)
{
  asection *sgot = bfd_get_section_by_name (abfd, ".got");

  if (sgot == NULL || (! maybe_excluded && (sgot->flags & SEC_EXCLUDE) != 0))
    return NULL;
  return sgot;
}