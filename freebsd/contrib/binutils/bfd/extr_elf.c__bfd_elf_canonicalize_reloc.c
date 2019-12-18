#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct elf_backend_data {TYPE_1__* s; } ;
typedef  TYPE_2__* sec_ptr ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asymbol ;
typedef  int /*<<< orphan*/  arelent ;
struct TYPE_6__ {unsigned int reloc_count; int /*<<< orphan*/ * relocation; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* slurp_reloc_table ) (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 struct elf_backend_data* get_elf_backend_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

long
_bfd_elf_canonicalize_reloc (bfd *abfd,
			     sec_ptr section,
			     arelent **relptr,
			     asymbol **symbols)
{
  arelent *tblptr;
  unsigned int i;
  const struct elf_backend_data *bed = get_elf_backend_data (abfd);

  if (! bed->s->slurp_reloc_table (abfd, section, symbols, FALSE))
    return -1;

  tblptr = section->relocation;
  for (i = 0; i < section->reloc_count; i++)
    *relptr++ = tblptr++;

  *relptr = NULL;

  return section->reloc_count;
}