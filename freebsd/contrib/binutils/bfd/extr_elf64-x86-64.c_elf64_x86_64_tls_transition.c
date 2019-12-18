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
struct bfd_link_info {scalar_t__ shared; } ;

/* Variables and functions */
#define  R_X86_64_GOTPC32_TLSDESC 132 
#define  R_X86_64_GOTTPOFF 131 
#define  R_X86_64_TLSDESC_CALL 130 
#define  R_X86_64_TLSGD 129 
#define  R_X86_64_TLSLD 128 
 int R_X86_64_TPOFF32 ; 

__attribute__((used)) static int
elf64_x86_64_tls_transition (struct bfd_link_info *info, int r_type, int is_local)
{
  if (info->shared)
    return r_type;

  switch (r_type)
    {
    case R_X86_64_TLSGD:
    case R_X86_64_GOTPC32_TLSDESC:
    case R_X86_64_TLSDESC_CALL:
    case R_X86_64_GOTTPOFF:
      if (is_local)
	return R_X86_64_TPOFF32;
      return R_X86_64_GOTTPOFF;
    case R_X86_64_TLSLD:
      return R_X86_64_TPOFF32;
    }

   return r_type;
}