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
 scalar_t__ ppc_obj64 ; 
 scalar_t__ target_big_endian ; 

extern char*
ppc_target_format (void)
{
#ifdef OBJ_COFF
#ifdef TE_PE
  return target_big_endian ? "pe-powerpc" : "pe-powerpcle";
#elif TE_POWERMAC
  return "xcoff-powermac";
#else
#  ifdef TE_AIX5
    return (ppc_obj64 ? "aix5coff64-rs6000" : "aixcoff-rs6000");
#  else
    return (ppc_obj64 ? "aixcoff64-rs6000" : "aixcoff-rs6000");
#  endif
#endif
#endif
#ifdef OBJ_ELF
# ifdef TE_VXWORKS
  return "elf32-powerpc-vxworks";
# else
  return (target_big_endian
	  ? (ppc_obj64 ? "elf64-powerpc-freebsd" : "elf32-powerpc-freebsd")
	  : (ppc_obj64 ? "elf64-powerpcle" : "elf32-powerpcle"));
# endif
#endif
}