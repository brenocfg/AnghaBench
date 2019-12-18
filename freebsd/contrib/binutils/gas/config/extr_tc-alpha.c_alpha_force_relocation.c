#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int fx_r_type; } ;
typedef  TYPE_1__ fixS ;

/* Variables and functions */
#define  BFD_RELOC_ALPHA_BRSGP 150 
#define  BFD_RELOC_ALPHA_CODEADDR 149 
#define  BFD_RELOC_ALPHA_DTPREL16 148 
#define  BFD_RELOC_ALPHA_DTPREL_HI16 147 
#define  BFD_RELOC_ALPHA_DTPREL_LO16 146 
#define  BFD_RELOC_ALPHA_ELF_LITERAL 145 
#define  BFD_RELOC_ALPHA_GOTDTPREL16 144 
#define  BFD_RELOC_ALPHA_GOTTPREL16 143 
#define  BFD_RELOC_ALPHA_GPDISP 142 
#define  BFD_RELOC_ALPHA_GPDISP_HI16 141 
#define  BFD_RELOC_ALPHA_GPDISP_LO16 140 
#define  BFD_RELOC_ALPHA_GPREL_HI16 139 
#define  BFD_RELOC_ALPHA_GPREL_LO16 138 
#define  BFD_RELOC_ALPHA_LINKAGE 137 
#define  BFD_RELOC_ALPHA_LITERAL 136 
#define  BFD_RELOC_ALPHA_LITUSE 135 
#define  BFD_RELOC_ALPHA_TLSGD 134 
#define  BFD_RELOC_ALPHA_TLSLDM 133 
#define  BFD_RELOC_ALPHA_TPREL16 132 
#define  BFD_RELOC_ALPHA_TPREL_HI16 131 
#define  BFD_RELOC_ALPHA_TPREL_LO16 130 
#define  BFD_RELOC_GPREL16 129 
#define  BFD_RELOC_GPREL32 128 
 scalar_t__ alpha_flag_relax ; 
 int generic_force_reloc (TYPE_1__*) ; 

int
alpha_force_relocation (fixS *f)
{
  if (alpha_flag_relax)
    return 1;

  switch (f->fx_r_type)
    {
    case BFD_RELOC_ALPHA_GPDISP_HI16:
    case BFD_RELOC_ALPHA_GPDISP_LO16:
    case BFD_RELOC_ALPHA_GPDISP:
    case BFD_RELOC_ALPHA_LITERAL:
    case BFD_RELOC_ALPHA_ELF_LITERAL:
    case BFD_RELOC_ALPHA_LITUSE:
    case BFD_RELOC_GPREL16:
    case BFD_RELOC_GPREL32:
    case BFD_RELOC_ALPHA_GPREL_HI16:
    case BFD_RELOC_ALPHA_GPREL_LO16:
    case BFD_RELOC_ALPHA_LINKAGE:
    case BFD_RELOC_ALPHA_CODEADDR:
    case BFD_RELOC_ALPHA_BRSGP:
    case BFD_RELOC_ALPHA_TLSGD:
    case BFD_RELOC_ALPHA_TLSLDM:
    case BFD_RELOC_ALPHA_GOTDTPREL16:
    case BFD_RELOC_ALPHA_DTPREL_HI16:
    case BFD_RELOC_ALPHA_DTPREL_LO16:
    case BFD_RELOC_ALPHA_DTPREL16:
    case BFD_RELOC_ALPHA_GOTTPREL16:
    case BFD_RELOC_ALPHA_TPREL_HI16:
    case BFD_RELOC_ALPHA_TPREL_LO16:
    case BFD_RELOC_ALPHA_TPREL16:
      return 1;

    default:
      break;
    }

  return generic_force_reloc (f);
}