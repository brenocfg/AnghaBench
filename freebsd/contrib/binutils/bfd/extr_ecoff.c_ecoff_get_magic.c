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

/* Variables and functions */
 int ALPHA_MAGIC ; 
 int MIPS_MAGIC_BIG ; 
 int MIPS_MAGIC_BIG2 ; 
 int MIPS_MAGIC_BIG3 ; 
 int MIPS_MAGIC_LITTLE ; 
 int MIPS_MAGIC_LITTLE2 ; 
 int MIPS_MAGIC_LITTLE3 ; 
 int /*<<< orphan*/  abort () ; 
#define  bfd_arch_alpha 132 
#define  bfd_arch_mips 131 
 int /*<<< orphan*/  bfd_big_endian (int /*<<< orphan*/ *) ; 
 int bfd_get_arch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_get_mach (int /*<<< orphan*/ *) ; 
#define  bfd_mach_mips3000 130 
#define  bfd_mach_mips4000 129 
#define  bfd_mach_mips6000 128 

__attribute__((used)) static int
ecoff_get_magic (bfd *abfd)
{
  int big, little;

  switch (bfd_get_arch (abfd))
    {
    case bfd_arch_mips:
      switch (bfd_get_mach (abfd))
	{
	default:
	case 0:
	case bfd_mach_mips3000:
	  big = MIPS_MAGIC_BIG;
	  little = MIPS_MAGIC_LITTLE;
	  break;

	case bfd_mach_mips6000:
	  big = MIPS_MAGIC_BIG2;
	  little = MIPS_MAGIC_LITTLE2;
	  break;

	case bfd_mach_mips4000:
	  big = MIPS_MAGIC_BIG3;
	  little = MIPS_MAGIC_LITTLE3;
	  break;
	}

      return bfd_big_endian (abfd) ? big : little;

    case bfd_arch_alpha:
      return ALPHA_MAGIC;

    default:
      abort ();
      return 0;
    }
}