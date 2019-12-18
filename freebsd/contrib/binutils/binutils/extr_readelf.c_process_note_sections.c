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
typedef  int /*<<< orphan*/  bfd_vma ;
struct TYPE_5__ {unsigned long e_shnum; } ;
struct TYPE_4__ {scalar_t__ sh_type; scalar_t__ sh_size; scalar_t__ sh_offset; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ Elf_Internal_Shdr ;

/* Variables and functions */
 scalar_t__ SHT_NOTE ; 
 TYPE_3__ elf_header ; 
 int process_corefile_note_segment (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* section_headers ; 

__attribute__((used)) static int
process_note_sections (FILE *file)
{
  Elf_Internal_Shdr *section;
  unsigned long i;
  int res = 1;

  for (i = 0, section = section_headers;
       i < elf_header.e_shnum;
       i++, section++)
    if (section->sh_type == SHT_NOTE)
      res &= process_corefile_note_segment (file,
					    (bfd_vma) section->sh_offset,
					    (bfd_vma) section->sh_size);

  return res;
}