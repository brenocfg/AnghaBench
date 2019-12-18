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
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int EF_IA_64_ABI64 ; 
 int EF_IA_64_BE ; 
 scalar_t__ OUTPUT_FLAVOR ; 
 scalar_t__ bfd_target_elf_flavour ; 
 TYPE_1__ md ; 

const char *
ia64_target_format ()
{
  if (OUTPUT_FLAVOR == bfd_target_elf_flavour)
    {
      if (md.flags & EF_IA_64_BE)
	{
	  if (md.flags & EF_IA_64_ABI64)
#if defined(TE_AIX50)
	    return "elf64-ia64-aix-big";
#elif defined(TE_HPUX)
	    return "elf64-ia64-hpux-big";
#else
	    return "elf64-ia64-big";
#endif
	  else
#if defined(TE_AIX50)
	    return "elf32-ia64-aix-big";
#elif defined(TE_HPUX)
	    return "elf32-ia64-hpux-big";
#else
	    return "elf32-ia64-big";
#endif
	}
      else
	{
	  if (md.flags & EF_IA_64_ABI64)
#if defined(TE_AIX50)
	    return "elf64-ia64-aix-little";
#elif defined(TE_FreeBSD)
	    return "elf64-ia64-freebsd";
#else
	    return "elf64-ia64-little";
#endif
	  else
#ifdef TE_AIX50
	    return "elf32-ia64-aix-little";
#else
	    return "elf32-ia64-little";
#endif
	}
    }
  else
    return "unknown-format";
}