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
struct bfd_link_info {int dummy; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  bfd_elf_final_link (int /*<<< orphan*/ *,struct bfd_link_info*) ; 
 int /*<<< orphan*/  bfd_elf_gc_common_finalize_got_offsets (int /*<<< orphan*/ *,struct bfd_link_info*) ; 

bfd_boolean
bfd_elf_gc_common_final_link (bfd *abfd, struct bfd_link_info *info)
{
  if (!bfd_elf_gc_common_finalize_got_offsets (abfd, info))
    return FALSE;

  /* Invoke the regular ELF backend linker to do all the work.  */
  return bfd_elf_final_link (abfd, info);
}