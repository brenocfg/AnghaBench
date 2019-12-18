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
typedef  scalar_t__ bfd_size_type ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 int SEC_ALLOC ; 
 scalar_t__ bfd_find_nearest_line (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bfd_get_section_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_get_section_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  filename ; 
 scalar_t__ found ; 
 int /*<<< orphan*/  functionname ; 
 int /*<<< orphan*/  line ; 
 scalar_t__ pc ; 
 int /*<<< orphan*/  syms ; 

__attribute__((used)) static void
find_offset_in_section (bfd *abfd, asection *section)
{
  bfd_size_type size;

  if (found)
    return;

  if ((bfd_get_section_flags (abfd, section) & SEC_ALLOC) == 0)
    return;

  size = bfd_get_section_size (section);
  if (pc >= size)
    return;

  found = bfd_find_nearest_line (abfd, section, syms, pc,
				 &filename, &functionname, &line);
}