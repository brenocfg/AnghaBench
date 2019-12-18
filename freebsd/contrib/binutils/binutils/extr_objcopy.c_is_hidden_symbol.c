#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  st_other; } ;
struct TYPE_8__ {TYPE_1__ internal_elf_sym; } ;
typedef  TYPE_2__ elf_symbol_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_9__ {int /*<<< orphan*/  the_bfd; } ;
typedef  TYPE_3__ asymbol ;

/* Variables and functions */
 int ELF_ST_VISIBILITY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
#define  STV_HIDDEN 129 
#define  STV_INTERNAL 128 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__* elf_symbol_from (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static bfd_boolean
is_hidden_symbol (asymbol *sym)
{
  elf_symbol_type *elf_sym;

  elf_sym = elf_symbol_from (sym->the_bfd, sym);
  if (elf_sym != NULL)
    switch (ELF_ST_VISIBILITY (elf_sym->internal_elf_sym.st_other))
      {
      case STV_HIDDEN:
      case STV_INTERNAL:
	return TRUE;
      }
  return FALSE;
}