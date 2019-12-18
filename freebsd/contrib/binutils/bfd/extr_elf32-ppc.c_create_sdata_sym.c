#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ppc_elf_link_hash_table {int /*<<< orphan*/  elf; } ;
struct TYPE_6__ {TYPE_3__* sym; int /*<<< orphan*/  sym_name; } ;
typedef  TYPE_2__ elf_linker_section_t ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_5__ {scalar_t__ type; } ;
struct TYPE_7__ {int ref_regular; scalar_t__ non_elf; TYPE_1__ root; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ bfd_link_hash_new ; 
 TYPE_3__* elf_link_hash_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_boolean
create_sdata_sym (struct ppc_elf_link_hash_table *htab,
		  elf_linker_section_t *lsect)
{
  lsect->sym = elf_link_hash_lookup (&htab->elf, lsect->sym_name,
				     TRUE, FALSE, TRUE);
  if (lsect->sym == NULL)
    return FALSE;
  if (lsect->sym->root.type == bfd_link_hash_new)
    lsect->sym->non_elf = 0;
  lsect->sym->ref_regular = 1;
  return TRUE;
}