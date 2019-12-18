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
typedef  int flagword ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {int e_flags; } ;

/* Variables and functions */
 int EF_MIPS_ARCH ; 
 int EF_MIPS_MACH ; 
 int E_MIPS_ARCH_1 ; 
 int E_MIPS_ARCH_2 ; 
 int E_MIPS_ARCH_3 ; 
 int E_MIPS_ARCH_32 ; 
 int E_MIPS_ARCH_32R2 ; 
 int E_MIPS_ARCH_4 ; 
 int E_MIPS_ARCH_5 ; 
 int E_MIPS_ARCH_64 ; 
 int E_MIPS_ARCH_64R2 ; 
 int E_MIPS_MACH_3900 ; 
 int E_MIPS_MACH_4010 ; 
 int E_MIPS_MACH_4100 ; 
 int E_MIPS_MACH_4111 ; 
 int E_MIPS_MACH_4120 ; 
 int E_MIPS_MACH_4650 ; 
 int E_MIPS_MACH_5400 ; 
 int E_MIPS_MACH_5500 ; 
 int E_MIPS_MACH_9000 ; 
 int E_MIPS_MACH_OCTEON ; 
 int E_MIPS_MACH_SB1 ; 
 int bfd_get_mach (int /*<<< orphan*/ *) ; 
#define  bfd_mach_mips10000 154 
#define  bfd_mach_mips12000 153 
#define  bfd_mach_mips3000 152 
#define  bfd_mach_mips3900 151 
#define  bfd_mach_mips4000 150 
#define  bfd_mach_mips4010 149 
#define  bfd_mach_mips4100 148 
#define  bfd_mach_mips4111 147 
#define  bfd_mach_mips4120 146 
#define  bfd_mach_mips4300 145 
#define  bfd_mach_mips4400 144 
#define  bfd_mach_mips4600 143 
#define  bfd_mach_mips4650 142 
#define  bfd_mach_mips5 141 
#define  bfd_mach_mips5000 140 
#define  bfd_mach_mips5400 139 
#define  bfd_mach_mips5500 138 
#define  bfd_mach_mips6000 137 
#define  bfd_mach_mips7000 136 
#define  bfd_mach_mips8000 135 
#define  bfd_mach_mips9000 134 
#define  bfd_mach_mips_octeon 133 
#define  bfd_mach_mips_sb1 132 
#define  bfd_mach_mipsisa32 131 
#define  bfd_mach_mipsisa32r2 130 
#define  bfd_mach_mipsisa64 129 
#define  bfd_mach_mipsisa64r2 128 
 TYPE_1__* elf_elfheader (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mips_set_isa_flags (bfd *abfd)
{
  flagword val;

  switch (bfd_get_mach (abfd))
    {
    default:
    case bfd_mach_mips3000:
      val = E_MIPS_ARCH_1;
      break;

    case bfd_mach_mips3900:
      val = E_MIPS_ARCH_1 | E_MIPS_MACH_3900;
      break;

    case bfd_mach_mips6000:
      val = E_MIPS_ARCH_2;
      break;

    case bfd_mach_mips4000:
    case bfd_mach_mips4300:
    case bfd_mach_mips4400:
    case bfd_mach_mips4600:
      val = E_MIPS_ARCH_3;
      break;

    case bfd_mach_mips4010:
      val = E_MIPS_ARCH_3 | E_MIPS_MACH_4010;
      break;

    case bfd_mach_mips4100:
      val = E_MIPS_ARCH_3 | E_MIPS_MACH_4100;
      break;

    case bfd_mach_mips4111:
      val = E_MIPS_ARCH_3 | E_MIPS_MACH_4111;
      break;

    case bfd_mach_mips4120:
      val = E_MIPS_ARCH_3 | E_MIPS_MACH_4120;
      break;

    case bfd_mach_mips4650:
      val = E_MIPS_ARCH_3 | E_MIPS_MACH_4650;
      break;

    case bfd_mach_mips5400:
      val = E_MIPS_ARCH_4 | E_MIPS_MACH_5400;
      break;

    case bfd_mach_mips5500:
      val = E_MIPS_ARCH_4 | E_MIPS_MACH_5500;
      break;

    case bfd_mach_mips9000:
      val = E_MIPS_ARCH_4 | E_MIPS_MACH_9000;
      break;

    case bfd_mach_mips5000:
    case bfd_mach_mips7000:
    case bfd_mach_mips8000:
    case bfd_mach_mips10000:
    case bfd_mach_mips12000:
      val = E_MIPS_ARCH_4;
      break;

    case bfd_mach_mips5:
      val = E_MIPS_ARCH_5;
      break;

    case bfd_mach_mips_octeon:
      val = E_MIPS_ARCH_64R2 | E_MIPS_MACH_OCTEON;
      break;

    case bfd_mach_mips_sb1:
      val = E_MIPS_ARCH_64 | E_MIPS_MACH_SB1;
      break;

    case bfd_mach_mipsisa32:
      val = E_MIPS_ARCH_32;
      break;

    case bfd_mach_mipsisa64:
      val = E_MIPS_ARCH_64;
      break;

    case bfd_mach_mipsisa32r2:
      val = E_MIPS_ARCH_32R2;
      break;

    case bfd_mach_mipsisa64r2:
      val = E_MIPS_ARCH_64R2;
      break;
    }
  elf_elfheader (abfd)->e_flags &= ~(EF_MIPS_ARCH | EF_MIPS_MACH);
  elf_elfheader (abfd)->e_flags |= val;

}