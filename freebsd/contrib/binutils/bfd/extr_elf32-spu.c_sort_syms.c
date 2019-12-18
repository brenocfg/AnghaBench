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
typedef  scalar_t__ bfd_signed_vma ;
struct TYPE_5__ {int index; } ;
typedef  TYPE_1__ asection ;
struct TYPE_6__ {scalar_t__ st_value; scalar_t__ st_size; } ;
typedef  TYPE_2__ Elf_Internal_Sym ;

/* Variables and functions */
 TYPE_1__** sort_syms_psecs ; 
 TYPE_2__* const sort_syms_syms ; 

__attribute__((used)) static int
sort_syms (const void *a, const void *b)
{
  Elf_Internal_Sym *const *s1 = a;
  Elf_Internal_Sym *const *s2 = b;
  asection *sec1,*sec2;
  bfd_signed_vma delta;

  sec1 = sort_syms_psecs[*s1 - sort_syms_syms];
  sec2 = sort_syms_psecs[*s2 - sort_syms_syms];

  if (sec1 != sec2)
    return sec1->index - sec2->index;

  delta = (*s1)->st_value - (*s2)->st_value;
  if (delta != 0)
    return delta < 0 ? -1 : 1;

  delta = (*s2)->st_size - (*s1)->st_size;
  if (delta != 0)
    return delta < 0 ? -1 : 1;

  return *s1 < *s2 ? -1 : 1;
}