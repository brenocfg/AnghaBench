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
 char const* ELF64_TARGET_FORMAT ; 
 char const* ELF_TARGET_FORMAT ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ default_arch_type ; 
 int /*<<< orphan*/  default_init_p ; 
 int /*<<< orphan*/  init_default_arch () ; 
 scalar_t__ sparc86x ; 
 int sparc_arch_size ; 
 scalar_t__ target_big_endian ; 
 scalar_t__ target_little_endian_data ; 

const char *
sparc_target_format ()
{
  /* We don't get a chance to initialize anything before we're called,
     so handle that now.  */
  if (! default_init_p)
    init_default_arch ();

#ifdef OBJ_AOUT
#ifdef TE_NetBSD
  return "a.out-sparc-netbsd";
#else
#ifdef TE_SPARCAOUT
  if (target_big_endian)
    return "a.out-sunos-big";
  else if (default_arch_type == sparc86x && target_little_endian_data)
    return "a.out-sunos-big";
  else
    return "a.out-sparc-little";
#else
  return "a.out-sunos-big";
#endif
#endif
#endif

#ifdef OBJ_BOUT
  return "b.out.big";
#endif

#ifdef OBJ_COFF
#ifdef TE_LYNX
  return "coff-sparc-lynx";
#else
  return "coff-sparc";
#endif
#endif

#ifdef TE_VXWORKS
  return "elf32-sparc-vxworks";
#endif

#ifdef OBJ_ELF
  return sparc_arch_size == 64 ? ELF64_TARGET_FORMAT : ELF_TARGET_FORMAT;
#endif

  abort ();
}