#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  e_phnum; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  Elf_Internal_Phdr ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * cmalloc (int /*<<< orphan*/ ,int) ; 
 TYPE_1__ elf_header ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ get_32bit_program_headers (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ get_64bit_program_headers (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ is_32bit_elf ; 
 int /*<<< orphan*/ * program_headers ; 

__attribute__((used)) static int
get_program_headers (FILE *file)
{
  Elf_Internal_Phdr *phdrs;

  /* Check cache of prior read.  */
  if (program_headers != NULL)
    return 1;

  phdrs = cmalloc (elf_header.e_phnum, sizeof (Elf_Internal_Phdr));

  if (phdrs == NULL)
    {
      error (_("Out of memory\n"));
      return 0;
    }

  if (is_32bit_elf
      ? get_32bit_program_headers (file, phdrs)
      : get_64bit_program_headers (file, phdrs))
    {
      program_headers = phdrs;
      return 1;
    }

  free (phdrs);
  return 0;
}