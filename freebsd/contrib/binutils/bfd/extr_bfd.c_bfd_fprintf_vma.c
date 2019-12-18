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
typedef  int bfd_vma ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {int /*<<< orphan*/  (* elf_backend_fprintf_vma ) (int /*<<< orphan*/ *,void*,int) ;} ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ bfd_get_flavour (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_get_target (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_target_elf_flavour ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,unsigned long) ; 
 int /*<<< orphan*/  fprintf_vma (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* get_elf_backend_data (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * strstr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,void*,int) ; 

void
bfd_fprintf_vma (bfd *abfd, void *stream, bfd_vma value)
{
  if (bfd_get_flavour (abfd) == bfd_target_elf_flavour)
    get_elf_backend_data (abfd)->elf_backend_fprintf_vma (abfd, stream, value);
#ifdef BFD64
  /* fprintf_vma() on a 64-bit enabled host will always print a 64-bit
     value, but really we want to display the address in the target's
     address size.  Since we do not have a field in the bfd structure
     to tell us this, we take a guess, based on the target's name.  */
  else if (strstr (bfd_get_target (abfd), "64") == NULL
	   && strcmp (bfd_get_target (abfd), "mmo") != 0)
    fprintf ((FILE *) stream, "%08lx", (unsigned long) (value & 0xffffffff));
#endif
  else
    fprintf_vma ((FILE *) stream, value);
}