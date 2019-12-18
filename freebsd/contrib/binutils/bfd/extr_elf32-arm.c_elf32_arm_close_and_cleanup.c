#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_5__ {scalar_t__ sections; } ;
typedef  TYPE_1__ bfd ;

/* Variables and functions */
 int /*<<< orphan*/  _bfd_elf_close_and_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  bfd_map_over_sections (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unrecord_section_via_map_over_sections ; 

__attribute__((used)) static bfd_boolean
elf32_arm_close_and_cleanup (bfd * abfd)
{
  if (abfd->sections)
    bfd_map_over_sections (abfd,
			   unrecord_section_via_map_over_sections,
			   NULL);

  return _bfd_elf_close_and_cleanup (abfd);
}