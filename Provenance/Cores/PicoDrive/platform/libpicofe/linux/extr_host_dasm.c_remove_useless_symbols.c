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
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* name; int flags; scalar_t__ value; TYPE_3__* section; } ;
typedef  TYPE_1__ asymbol ;
struct TYPE_6__ {scalar_t__ vma; } ;

/* Variables and functions */
 int BSF_DEBUGGING ; 
 int BSF_SECTION_SYM ; 
 scalar_t__ bfd_is_com_section (TYPE_3__*) ; 
 scalar_t__ bfd_is_und_section (TYPE_3__*) ; 

__attribute__((used)) static long
remove_useless_symbols (asymbol **symbols, long count)
{
  asymbol **in_ptr = symbols, **out_ptr = symbols;

  while (--count >= 0)
    {
      asymbol *sym = *in_ptr++;

      if (sym->name == NULL || sym->name[0] == '\0' || sym->name[0] == '$')
        continue;
      if (sym->flags & (BSF_DEBUGGING | BSF_SECTION_SYM))
        continue;
      if (bfd_is_und_section (sym->section)
          || bfd_is_com_section (sym->section))
        continue;
      if (sym->value + sym->section->vma == 0)
        continue;
/*
      printf("sym: %08lx %04x %08x v %08x \"%s\"\n",
        (unsigned int)sym->value, (unsigned int)sym->flags, (unsigned int)sym->udata.i,
        (unsigned int)sym->section->vma, sym->name);
*/
      *out_ptr++ = sym;
    }

  return out_ptr - symbols;
}