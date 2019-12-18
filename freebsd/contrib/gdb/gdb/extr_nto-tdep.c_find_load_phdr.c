#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_7__ {unsigned int e_phnum; } ;
struct TYPE_6__ {TYPE_1__* phdr; } ;
struct TYPE_5__ {scalar_t__ p_type; int p_flags; } ;
typedef  TYPE_1__ Elf_Internal_Phdr ;

/* Variables and functions */
 int PF_X ; 
 scalar_t__ PT_LOAD ; 
 TYPE_4__* elf_elfheader (int /*<<< orphan*/ *) ; 
 TYPE_3__* elf_tdata (int /*<<< orphan*/ *) ; 

Elf_Internal_Phdr *
find_load_phdr (bfd *abfd)
{
  Elf_Internal_Phdr *phdr;
  unsigned int i;

  if (!elf_tdata (abfd))
    return NULL;

  phdr = elf_tdata (abfd)->phdr;
  for (i = 0; i < elf_elfheader (abfd)->e_phnum; i++, phdr++)
    {
      if (phdr->p_type == PT_LOAD && (phdr->p_flags & PF_X))
	return phdr;
    }
  return NULL;
}