#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ bfd_vma ;
struct TYPE_5__ {scalar_t__ value; char const* name; TYPE_1__* section; } ;
typedef  TYPE_2__ asymbol ;
struct TYPE_4__ {scalar_t__ vma; } ;

/* Variables and functions */
 TYPE_2__** symbols ; 
 int symcount ; 

__attribute__((used)) static const char *lookup_name(bfd_vma addr)
{
  asymbol **sptr = symbols;
  int i;

  for (i = 0; i < symcount; i++) {
    asymbol *sym = *sptr++;

    if (addr == sym->value + sym->section->vma)
      return sym->name;
  }

  return NULL;
}