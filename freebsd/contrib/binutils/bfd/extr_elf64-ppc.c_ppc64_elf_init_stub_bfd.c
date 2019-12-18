#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * dynobj; } ;
struct ppc_link_hash_table {TYPE_1__ elf; int /*<<< orphan*/ * stub_bfd; } ;
struct bfd_link_info {int dummy; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_4__ {int /*<<< orphan*/ * e_ident; } ;

/* Variables and functions */
 size_t EI_CLASS ; 
 int /*<<< orphan*/  ELFCLASS64 ; 
 TYPE_2__* elf_elfheader (int /*<<< orphan*/ *) ; 
 struct ppc_link_hash_table* ppc_hash_table (struct bfd_link_info*) ; 

void
ppc64_elf_init_stub_bfd (bfd *abfd, struct bfd_link_info *info)
{
  struct ppc_link_hash_table *htab;

  elf_elfheader (abfd)->e_ident[EI_CLASS] = ELFCLASS64;

/* Always hook our dynamic sections into the first bfd, which is the
   linker created stub bfd.  This ensures that the GOT header is at
   the start of the output TOC section.  */
  htab = ppc_hash_table (info);
  htab->stub_bfd = abfd;
  htab->elf.dynobj = abfd;
}