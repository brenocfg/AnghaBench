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
struct bfd_link_info {scalar_t__ shared; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {int /*<<< orphan*/  has_tlsgd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABI_64_P (int /*<<< orphan*/ *) ; 
 int R_SPARC_REV32 ; 
#define  R_SPARC_TLS_GD_HI22 133 
#define  R_SPARC_TLS_GD_LO10 132 
#define  R_SPARC_TLS_IE_HI22 131 
#define  R_SPARC_TLS_IE_LO10 130 
#define  R_SPARC_TLS_LDM_HI22 129 
#define  R_SPARC_TLS_LDM_LO10 128 
 int R_SPARC_TLS_LE_HIX22 ; 
 int R_SPARC_TLS_LE_LOX10 ; 
 TYPE_1__* _bfd_sparc_elf_tdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
sparc_elf_tls_transition (struct bfd_link_info *info, bfd *abfd,
			  int r_type, int is_local)
{
  if (! ABI_64_P (abfd)
      && r_type == R_SPARC_TLS_GD_HI22
      && ! _bfd_sparc_elf_tdata (abfd)->has_tlsgd)
    r_type = R_SPARC_REV32;

  if (info->shared)
    return r_type;

  switch (r_type)
    {
    case R_SPARC_TLS_GD_HI22:
      if (is_local)
	return R_SPARC_TLS_LE_HIX22;
      return R_SPARC_TLS_IE_HI22;
    case R_SPARC_TLS_GD_LO10:
      if (is_local)
	return R_SPARC_TLS_LE_LOX10;
      return R_SPARC_TLS_IE_LO10;
    case R_SPARC_TLS_IE_HI22:
      if (is_local)
	return R_SPARC_TLS_LE_HIX22;
      return r_type;
    case R_SPARC_TLS_IE_LO10:
      if (is_local)
	return R_SPARC_TLS_LE_LOX10;
      return r_type;
    case R_SPARC_TLS_LDM_HI22:
      return R_SPARC_TLS_LE_HIX22;
    case R_SPARC_TLS_LDM_LO10:
      return R_SPARC_TLS_LE_LOX10;
    }

  return r_type;
}