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
#define  R_386_TLS_DESC_CALL 134 
#define  R_386_TLS_GD 133 
#define  R_386_TLS_GOTDESC 132 
#define  R_386_TLS_GOTIE 131 
#define  R_386_TLS_IE 130 
#define  R_386_TLS_IE_32 129 
#define  R_386_TLS_LDM 128 
 int R_386_TLS_LE_32 ; 

__attribute__((used)) static int
elf_i386_tls_transition (struct bfd_link_info *info, int r_type, int is_local)
{
  if (info->shared)
    return r_type;

  switch (r_type)
    {
    case R_386_TLS_GD:
    case R_386_TLS_GOTDESC:
    case R_386_TLS_DESC_CALL:
    case R_386_TLS_IE_32:
      if (is_local)
	return R_386_TLS_LE_32;
      return R_386_TLS_IE_32;
    case R_386_TLS_IE:
    case R_386_TLS_GOTIE:
      if (is_local)
	return R_386_TLS_LE_32;
      return r_type;
    case R_386_TLS_LDM:
      return R_386_TLS_LE_32;
    }

  return r_type;
}