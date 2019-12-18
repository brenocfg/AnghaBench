#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct elf_strtab_hash {int dummy; } ;
struct TYPE_4__ {scalar_t__ link; } ;
struct TYPE_5__ {TYPE_1__ i; } ;
struct TYPE_6__ {scalar_t__ type; TYPE_2__ u; } ;
struct elf_link_hash_entry {int dynindx; int /*<<< orphan*/  dynstr_index; TYPE_3__ root; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _bfd_elf_strtab_offset (struct elf_strtab_hash*,int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_link_hash_warning ; 

__attribute__((used)) static bfd_boolean
elf_adjust_dynstr_offsets (struct elf_link_hash_entry *h, void *data)
{
  struct elf_strtab_hash *dynstr = data;

  if (h->root.type == bfd_link_hash_warning)
    h = (struct elf_link_hash_entry *) h->root.u.i.link;

  if (h->dynindx != -1)
    h->dynstr_index = _bfd_elf_strtab_offset (dynstr, h->dynstr_index);
  return TRUE;
}