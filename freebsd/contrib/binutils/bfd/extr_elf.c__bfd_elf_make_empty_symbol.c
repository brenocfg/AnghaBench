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
struct TYPE_6__ {int /*<<< orphan*/ * the_bfd; } ;
struct TYPE_5__ {TYPE_2__ symbol; } ;
typedef  TYPE_1__ elf_symbol_type ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd ;
typedef  TYPE_2__ asymbol ;

/* Variables and functions */
 TYPE_1__* bfd_zalloc (int /*<<< orphan*/ *,int) ; 

asymbol *
_bfd_elf_make_empty_symbol (bfd *abfd)
{
  elf_symbol_type *newsym;
  bfd_size_type amt = sizeof (elf_symbol_type);

  newsym = bfd_zalloc (abfd, amt);
  if (!newsym)
    return NULL;
  else
    {
      newsym->symbol.the_bfd = abfd;
      return &newsym->symbol;
    }
}