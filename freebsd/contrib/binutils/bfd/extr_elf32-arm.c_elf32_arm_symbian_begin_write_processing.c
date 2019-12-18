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
struct bfd_link_info {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ bfd ;

/* Variables and functions */
 int /*<<< orphan*/  D_PAGED ; 
 int /*<<< orphan*/  elf32_arm_begin_write_processing (TYPE_1__*,struct bfd_link_info*) ; 

__attribute__((used)) static void
elf32_arm_symbian_begin_write_processing (bfd *abfd, 
					  struct bfd_link_info *link_info)
{
  /* BPABI objects are never loaded directly by an OS kernel; they are
     processed by a postlinker first, into an OS-specific format.  If
     the D_PAGED bit is set on the file, BFD will align segments on
     page boundaries, so that an OS can directly map the file.  With
     BPABI objects, that just results in wasted space.  In addition,
     because we clear the D_PAGED bit, map_sections_to_segments will
     recognize that the program headers should not be mapped into any
     loadable segment.  */
  abfd->flags &= ~D_PAGED;
  elf32_arm_begin_write_processing(abfd, link_info);
}