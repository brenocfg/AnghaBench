#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {struct TYPE_9__* prev; int /*<<< orphan*/  symbol; } ;
typedef  TYPE_3__ tekhex_symbol_type ;
struct TYPE_8__ {TYPE_1__* tekhex_data; } ;
struct TYPE_10__ {TYPE_2__ tdata; } ;
typedef  TYPE_4__ bfd ;
typedef  int /*<<< orphan*/  asymbol ;
struct TYPE_7__ {TYPE_3__* symbols; } ;

/* Variables and functions */
 long bfd_get_symcount (TYPE_4__*) ; 

__attribute__((used)) static long
tekhex_canonicalize_symtab (bfd *abfd, asymbol **table)
{
  tekhex_symbol_type *p = abfd->tdata.tekhex_data->symbols;
  unsigned int c = bfd_get_symcount (abfd);

  table[c] = 0;
  while (p)
    {
      table[--c] = &(p->symbol);
      p = p->prev;
    }

  return bfd_get_symcount (abfd);
}