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
struct bfd_link_info {int /*<<< orphan*/  hash; } ;
struct TYPE_3__ {int /*<<< orphan*/  sec_info_type; int /*<<< orphan*/  vma; int /*<<< orphan*/  output_offset; int /*<<< orphan*/  output_section; } ;
typedef  TYPE_1__ asection ;

/* Variables and functions */
 int /*<<< orphan*/  ELF_INFO_TYPE_JUST_SYMS ; 
 int /*<<< orphan*/  bfd_abs_section_ptr ; 
 int /*<<< orphan*/  is_elf_hash_table (int /*<<< orphan*/ ) ; 

void
_bfd_elf_link_just_syms (asection *sec, struct bfd_link_info *info)
{
  sec->output_section = bfd_abs_section_ptr;
  sec->output_offset = sec->vma;
  if (!is_elf_hash_table (info->hash))
    return;

  sec->sec_info_type = ELF_INFO_TYPE_JUST_SYMS;
}