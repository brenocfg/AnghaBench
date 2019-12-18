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
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {int e_flags; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ABI_64_P (int /*<<< orphan*/ *) ; 
 scalar_t__ ABI_N32_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 int EF_MIPS_32BITMODE ; 
 int EF_MIPS_ABI ; 
 int EF_MIPS_ARCH ; 
 int EF_MIPS_ARCH_ASE_M16 ; 
 int EF_MIPS_ARCH_ASE_MDMX ; 
 int EF_MIPS_CPIC ; 
 int EF_MIPS_NOREORDER ; 
 int EF_MIPS_PIC ; 
 int EF_MIPS_UCODE ; 
 int EF_MIPS_XGOT ; 
 int E_MIPS_ABI_EABI32 ; 
 int E_MIPS_ABI_EABI64 ; 
 int E_MIPS_ABI_O32 ; 
 int E_MIPS_ABI_O64 ; 
 int E_MIPS_ARCH_1 ; 
 int E_MIPS_ARCH_2 ; 
 int E_MIPS_ARCH_3 ; 
 int E_MIPS_ARCH_32 ; 
 int E_MIPS_ARCH_32R2 ; 
 int E_MIPS_ARCH_4 ; 
 int E_MIPS_ARCH_5 ; 
 int E_MIPS_ARCH_64 ; 
 int E_MIPS_ARCH_64R2 ; 
 int /*<<< orphan*/  TRUE ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  _bfd_elf_print_private_bfd_data (int /*<<< orphan*/ *,void*) ; 
 TYPE_1__* elf_elfheader (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 

bfd_boolean
_bfd_mips_elf_print_private_bfd_data (bfd *abfd, void *ptr)
{
  FILE *file = ptr;

  BFD_ASSERT (abfd != NULL && ptr != NULL);

  /* Print normal ELF private data.  */
  _bfd_elf_print_private_bfd_data (abfd, ptr);

  /* xgettext:c-format */
  fprintf (file, _("private flags = %lx:"), elf_elfheader (abfd)->e_flags);

  if ((elf_elfheader (abfd)->e_flags & EF_MIPS_ABI) == E_MIPS_ABI_O32)
    fprintf (file, _(" [abi=O32]"));
  else if ((elf_elfheader (abfd)->e_flags & EF_MIPS_ABI) == E_MIPS_ABI_O64)
    fprintf (file, _(" [abi=O64]"));
  else if ((elf_elfheader (abfd)->e_flags & EF_MIPS_ABI) == E_MIPS_ABI_EABI32)
    fprintf (file, _(" [abi=EABI32]"));
  else if ((elf_elfheader (abfd)->e_flags & EF_MIPS_ABI) == E_MIPS_ABI_EABI64)
    fprintf (file, _(" [abi=EABI64]"));
  else if ((elf_elfheader (abfd)->e_flags & EF_MIPS_ABI))
    fprintf (file, _(" [abi unknown]"));
  else if (ABI_N32_P (abfd))
    fprintf (file, _(" [abi=N32]"));
  else if (ABI_64_P (abfd))
    fprintf (file, _(" [abi=64]"));
  else
    fprintf (file, _(" [no abi set]"));

  if ((elf_elfheader (abfd)->e_flags & EF_MIPS_ARCH) == E_MIPS_ARCH_1)
    fprintf (file, " [mips1]");
  else if ((elf_elfheader (abfd)->e_flags & EF_MIPS_ARCH) == E_MIPS_ARCH_2)
    fprintf (file, " [mips2]");
  else if ((elf_elfheader (abfd)->e_flags & EF_MIPS_ARCH) == E_MIPS_ARCH_3)
    fprintf (file, " [mips3]");
  else if ((elf_elfheader (abfd)->e_flags & EF_MIPS_ARCH) == E_MIPS_ARCH_4)
    fprintf (file, " [mips4]");
  else if ((elf_elfheader (abfd)->e_flags & EF_MIPS_ARCH) == E_MIPS_ARCH_5)
    fprintf (file, " [mips5]");
  else if ((elf_elfheader (abfd)->e_flags & EF_MIPS_ARCH) == E_MIPS_ARCH_32)
    fprintf (file, " [mips32]");
  else if ((elf_elfheader (abfd)->e_flags & EF_MIPS_ARCH) == E_MIPS_ARCH_64)
    fprintf (file, " [mips64]");
  else if ((elf_elfheader (abfd)->e_flags & EF_MIPS_ARCH) == E_MIPS_ARCH_32R2)
    fprintf (file, " [mips32r2]");
  else if ((elf_elfheader (abfd)->e_flags & EF_MIPS_ARCH) == E_MIPS_ARCH_64R2)
    fprintf (file, " [mips64r2]");
  else
    fprintf (file, _(" [unknown ISA]"));

  if (elf_elfheader (abfd)->e_flags & EF_MIPS_ARCH_ASE_MDMX)
    fprintf (file, " [mdmx]");

  if (elf_elfheader (abfd)->e_flags & EF_MIPS_ARCH_ASE_M16)
    fprintf (file, " [mips16]");

  if (elf_elfheader (abfd)->e_flags & EF_MIPS_32BITMODE)
    fprintf (file, " [32bitmode]");
  else
    fprintf (file, _(" [not 32bitmode]"));

  if (elf_elfheader (abfd)->e_flags & EF_MIPS_NOREORDER)
    fprintf (file, " [noreorder]");

  if (elf_elfheader (abfd)->e_flags & EF_MIPS_PIC)
    fprintf (file, " [PIC]");

  if (elf_elfheader (abfd)->e_flags & EF_MIPS_CPIC)
    fprintf (file, " [CPIC]");

  if (elf_elfheader (abfd)->e_flags & EF_MIPS_XGOT)
    fprintf (file, " [XGOT]");

  if (elf_elfheader (abfd)->e_flags & EF_MIPS_UCODE)
    fprintf (file, " [UCODE]");

  fputc ('\n', file);

  return TRUE;
}