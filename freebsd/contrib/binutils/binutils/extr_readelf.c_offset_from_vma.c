#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  long bfd_vma ;
typedef  scalar_t__ bfd_size_type ;
struct TYPE_5__ {int e_phnum; } ;
struct TYPE_4__ {scalar_t__ p_type; long p_vaddr; long p_align; scalar_t__ p_filesz; long p_offset; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ Elf_Internal_Phdr ;

/* Variables and functions */
 scalar_t__ PT_LOAD ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_3__ elf_header ; 
 int /*<<< orphan*/  get_program_headers (int /*<<< orphan*/ *) ; 
 TYPE_1__* program_headers ; 
 int /*<<< orphan*/  warn (int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static long
offset_from_vma (FILE *file, bfd_vma vma, bfd_size_type size)
{
  Elf_Internal_Phdr *seg;

  if (! get_program_headers (file))
    {
      warn (_("Cannot interpret virtual addresses without program headers.\n"));
      return (long) vma;
    }

  for (seg = program_headers;
       seg < program_headers + elf_header.e_phnum;
       ++seg)
    {
      if (seg->p_type != PT_LOAD)
	continue;

      if (vma >= (seg->p_vaddr & -seg->p_align)
	  && vma + size <= seg->p_vaddr + seg->p_filesz)
	return vma - seg->p_vaddr + seg->p_offset;
    }

  warn (_("Virtual address 0x%lx not located in any PT_LOAD segment.\n"),
	(long) vma);
  return (long) vma;
}