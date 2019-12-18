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
struct internal_filehdr {int f_magic; } ;
typedef  enum bfd_architecture { ____Placeholder_bfd_architecture } bfd_architecture ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
#define  ALPHA_MAGIC 135 
#define  MIPS_MAGIC_1 134 
#define  MIPS_MAGIC_BIG 133 
#define  MIPS_MAGIC_BIG2 132 
#define  MIPS_MAGIC_BIG3 131 
#define  MIPS_MAGIC_LITTLE 130 
#define  MIPS_MAGIC_LITTLE2 129 
#define  MIPS_MAGIC_LITTLE3 128 
 int bfd_arch_alpha ; 
 int bfd_arch_mips ; 
 int bfd_arch_obscure ; 
 int /*<<< orphan*/  bfd_default_set_arch_mach (int /*<<< orphan*/ *,int,unsigned long) ; 
 unsigned long bfd_mach_mips3000 ; 
 unsigned long bfd_mach_mips4000 ; 
 unsigned long bfd_mach_mips6000 ; 

bfd_boolean
_bfd_ecoff_set_arch_mach_hook (bfd *abfd, void * filehdr)
{
  struct internal_filehdr *internal_f = filehdr;
  enum bfd_architecture arch;
  unsigned long mach;

  switch (internal_f->f_magic)
    {
    case MIPS_MAGIC_1:
    case MIPS_MAGIC_LITTLE:
    case MIPS_MAGIC_BIG:
      arch = bfd_arch_mips;
      mach = bfd_mach_mips3000;
      break;

    case MIPS_MAGIC_LITTLE2:
    case MIPS_MAGIC_BIG2:
      /* MIPS ISA level 2: the r6000.  */
      arch = bfd_arch_mips;
      mach = bfd_mach_mips6000;
      break;

    case MIPS_MAGIC_LITTLE3:
    case MIPS_MAGIC_BIG3:
      /* MIPS ISA level 3: the r4000.  */
      arch = bfd_arch_mips;
      mach = bfd_mach_mips4000;
      break;

    case ALPHA_MAGIC:
      arch = bfd_arch_alpha;
      mach = 0;
      break;

    default:
      arch = bfd_arch_obscure;
      mach = 0;
      break;
    }

  return bfd_default_set_arch_mach (abfd, arch, mach);
}