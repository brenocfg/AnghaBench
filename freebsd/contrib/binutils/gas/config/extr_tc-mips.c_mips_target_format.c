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

/* Variables and functions */
 char const* ECOFF_LITTLE_FORMAT ; 
 int /*<<< orphan*/  HAVE_64BIT_OBJECTS ; 
 int /*<<< orphan*/  HAVE_NEWABI ; 
 int OUTPUT_FLAVOR ; 
 int /*<<< orphan*/  abort () ; 
#define  bfd_target_coff_flavour 130 
#define  bfd_target_ecoff_flavour 129 
#define  bfd_target_elf_flavour 128 
 int /*<<< orphan*/  target_big_endian ; 

const char *
mips_target_format (void)
{
  switch (OUTPUT_FLAVOR)
    {
    case bfd_target_ecoff_flavour:
      return target_big_endian ? "ecoff-bigmips" : ECOFF_LITTLE_FORMAT;
    case bfd_target_coff_flavour:
      return "pe-mips";
    case bfd_target_elf_flavour:
#ifdef TE_VXWORKS
      if (!HAVE_64BIT_OBJECTS && !HAVE_NEWABI)
	return (target_big_endian
		? "elf32-bigmips-vxworks"
		: "elf32-littlemips-vxworks");
#endif
#ifdef TE_TMIPS
      /* This is traditional mips.  */
      return (target_big_endian
	      ? (HAVE_64BIT_OBJECTS
		 ? "elf64-tradbigmips"
		 : (HAVE_NEWABI
		    ? "elf32-ntradbigmips" : "elf32-tradbigmips"))
	      : (HAVE_64BIT_OBJECTS
		 ? "elf64-tradlittlemips"
		 : (HAVE_NEWABI
		    ? "elf32-ntradlittlemips" : "elf32-tradlittlemips")));
#else
      return (target_big_endian
	      ? (HAVE_64BIT_OBJECTS
		 ? "elf64-bigmips"
		 : (HAVE_NEWABI
		    ? "elf32-nbigmips" : "elf32-bigmips"))
	      : (HAVE_64BIT_OBJECTS
		 ? "elf64-littlemips"
		 : (HAVE_NEWABI
		    ? "elf32-nlittlemips" : "elf32-littlemips")));
#endif
    default:
      abort ();
      return NULL;
    }
}