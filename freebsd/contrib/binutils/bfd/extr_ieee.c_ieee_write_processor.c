#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_3__ {int arch; int /*<<< orphan*/  mach; } ;
typedef  TYPE_1__ bfd_arch_info_type ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
#define  bfd_arch_h8300 161 
#define  bfd_arch_h8500 160 
#define  bfd_arch_i960 159 
#define  bfd_arch_m68k 158 
 TYPE_1__* bfd_get_arch_info (int /*<<< orphan*/ *) ; 
#define  bfd_mach_cpu32 157 
#define  bfd_mach_i960_ca 156 
#define  bfd_mach_i960_core 155 
#define  bfd_mach_i960_ka_sa 154 
#define  bfd_mach_i960_kb_sb 153 
#define  bfd_mach_i960_mc 152 
#define  bfd_mach_i960_xa 151 
#define  bfd_mach_m68000 150 
#define  bfd_mach_m68008 149 
#define  bfd_mach_m68010 148 
#define  bfd_mach_m68020 147 
#define  bfd_mach_m68030 146 
#define  bfd_mach_m68040 145 
#define  bfd_mach_m68060 144 
#define  bfd_mach_mcf_isa_a 143 
#define  bfd_mach_mcf_isa_a_emac 142 
#define  bfd_mach_mcf_isa_a_mac 141 
#define  bfd_mach_mcf_isa_a_nodiv 140 
#define  bfd_mach_mcf_isa_aplus 139 
#define  bfd_mach_mcf_isa_aplus_emac 138 
#define  bfd_mach_mcf_isa_aplus_mac 137 
#define  bfd_mach_mcf_isa_b 136 
#define  bfd_mach_mcf_isa_b_emac 135 
#define  bfd_mach_mcf_isa_b_float 134 
#define  bfd_mach_mcf_isa_b_float_emac 133 
#define  bfd_mach_mcf_isa_b_float_mac 132 
#define  bfd_mach_mcf_isa_b_mac 131 
#define  bfd_mach_mcf_isa_b_nousp 130 
#define  bfd_mach_mcf_isa_b_nousp_emac 129 
#define  bfd_mach_mcf_isa_b_nousp_mac 128 
 char const* bfd_printable_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee_write_id (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static bfd_boolean
ieee_write_processor (bfd *abfd)
{
  const bfd_arch_info_type *arch;

  arch = bfd_get_arch_info (abfd);
  switch (arch->arch)
    {
    default:
      if (! ieee_write_id (abfd, bfd_printable_name (abfd)))
	return FALSE;
      break;

    case bfd_arch_h8300:
      if (! ieee_write_id (abfd, "H8/300"))
	return FALSE;
      break;

    case bfd_arch_h8500:
      if (! ieee_write_id (abfd, "H8/500"))
	return FALSE;
      break;

    case bfd_arch_i960:
      switch (arch->mach)
	{
	default:
	case bfd_mach_i960_core:
	case bfd_mach_i960_ka_sa:
	  if (! ieee_write_id (abfd, "80960KA"))
	    return FALSE;
	  break;

	case bfd_mach_i960_kb_sb:
	  if (! ieee_write_id (abfd, "80960KB"))
	    return FALSE;
	  break;

	case bfd_mach_i960_ca:
	  if (! ieee_write_id (abfd, "80960CA"))
	    return FALSE;
	  break;

	case bfd_mach_i960_mc:
	case bfd_mach_i960_xa:
	  if (! ieee_write_id (abfd, "80960MC"))
	    return FALSE;
	  break;
	}
      break;

    case bfd_arch_m68k:
      {
	const char *id;

	switch (arch->mach)
	  {
	  default:		id = "68020"; break;
	  case bfd_mach_m68000: id = "68000"; break;
	  case bfd_mach_m68008: id = "68008"; break;
	  case bfd_mach_m68010: id = "68010"; break;
	  case bfd_mach_m68020: id = "68020"; break;
	  case bfd_mach_m68030: id = "68030"; break;
	  case bfd_mach_m68040: id = "68040"; break;
	  case bfd_mach_m68060: id = "68060"; break;
	  case bfd_mach_cpu32:  id = "cpu32"; break;
	  case bfd_mach_mcf_isa_a_nodiv: id = "isa-a:nodiv"; break;
	  case bfd_mach_mcf_isa_a: id = "isa-a"; break;
	  case bfd_mach_mcf_isa_a_mac: id = "isa-a:mac"; break;
	  case bfd_mach_mcf_isa_a_emac: id = "isa-a:emac"; break;
	  case bfd_mach_mcf_isa_aplus: id = "isa-aplus"; break;
	  case bfd_mach_mcf_isa_aplus_mac: id = "isa-aplus:mac"; break;
	  case bfd_mach_mcf_isa_aplus_emac: id = "isa-aplus:mac"; break;
	  case bfd_mach_mcf_isa_b_nousp: id = "isa-b:nousp"; break;
	  case bfd_mach_mcf_isa_b_nousp_mac: id = "isa-b:nousp:mac"; break;
	  case bfd_mach_mcf_isa_b_nousp_emac: id = "isa-b:nousp:emac"; break;
	  case bfd_mach_mcf_isa_b: id = "isa-b"; break;
	  case bfd_mach_mcf_isa_b_mac: id = "isa-b:mac"; break;
	  case bfd_mach_mcf_isa_b_emac: id = "isa-b:emac"; break;
	  case bfd_mach_mcf_isa_b_float: id = "isa-b:float"; break;
	  case bfd_mach_mcf_isa_b_float_mac: id = "isa-b:float:mac"; break;
	  case bfd_mach_mcf_isa_b_float_emac: id = "isa-b:float:emac"; break;
	  }

	if (! ieee_write_id (abfd, id))
	  return FALSE;
      }
      break;
    }

  return TRUE;
}