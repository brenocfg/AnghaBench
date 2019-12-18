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
struct elf_link_hash_entry {int forced_local; int dynindx; int /*<<< orphan*/  dynstr_index; scalar_t__ needs_plt; int /*<<< orphan*/  plt; } ;
struct bfd_link_info {int dummy; } ;
typedef  scalar_t__ bfd_boolean ;
struct TYPE_2__ {int /*<<< orphan*/  dynstr; int /*<<< orphan*/  init_plt_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  _bfd_elf_strtab_delref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* elf_hash_table (struct bfd_link_info*) ; 

void
_bfd_elf_link_hash_hide_symbol (struct bfd_link_info *info,
				struct elf_link_hash_entry *h,
				bfd_boolean force_local)
{
  h->plt = elf_hash_table (info)->init_plt_offset;
  h->needs_plt = 0;
  if (force_local)
    {
      h->forced_local = 1;
      if (h->dynindx != -1)
	{
	  h->dynindx = -1;
	  _bfd_elf_strtab_delref (elf_hash_table (info)->dynstr,
				  h->dynstr_index);
	}
    }
}