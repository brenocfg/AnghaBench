#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  Elf_Internal_Phdr ;
typedef  int /*<<< orphan*/  Elf_External_Phdr ;

/* Variables and functions */
 int bfd_bwrite (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_swap_phdr_out (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

int
elf_write_out_phdrs (bfd *abfd,
		     const Elf_Internal_Phdr *phdr,
		     unsigned int count)
{
  while (count--)
    {
      Elf_External_Phdr extphdr;
      elf_swap_phdr_out (abfd, phdr, &extphdr);
      if (bfd_bwrite (&extphdr, sizeof (Elf_External_Phdr), abfd)
	  != sizeof (Elf_External_Phdr))
	return -1;
      phdr++;
    }
  return 0;
}