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
struct TYPE_2__ {scalar_t__ type; } ;
struct elf_link_hash_entry {int dynindx; TYPE_1__ root; } ;
struct bfd_link_info {scalar_t__ pie; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bfd_elf_link_record_dynamic_symbol (struct bfd_link_info*,struct elf_link_hash_entry*) ; 
 scalar_t__ bfd_link_hash_undefweak ; 

bfd_boolean
_bfd_elf_link_hash_fixup_symbol (struct bfd_link_info *info,
				 struct elf_link_hash_entry *h)
{
  if (info->pie
      && h->dynindx == -1
      && h->root.type == bfd_link_hash_undefweak)
    return bfd_elf_link_record_dynamic_symbol (info, h);

  return TRUE;
}