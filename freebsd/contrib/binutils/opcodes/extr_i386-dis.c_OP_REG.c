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
 int DFLAG ; 
 char* INTERNAL_DISASSEMBLER_ERROR ; 
 int PREFIX_DATA ; 
 int REX_B ; 
 int REX_W ; 
 int /*<<< orphan*/  USED_REX (int) ; 
 int /*<<< orphan*/  address_mode ; 
#define  ah_reg 165 
#define  al_reg 164 
#define  ax_reg 163 
#define  bh_reg 162 
#define  bl_reg 161 
#define  bp_reg 160 
#define  bx_reg 159 
#define  ch_reg 158 
#define  cl_reg 157 
#define  cs_reg 156 
#define  cx_reg 155 
#define  dh_reg 154 
#define  di_reg 153 
#define  dl_reg 152 
#define  ds_reg 151 
#define  dx_reg 150 
#define  eAX_reg 149 
#define  eBP_reg 148 
#define  eBX_reg 147 
#define  eCX_reg 146 
#define  eDI_reg 145 
#define  eDX_reg 144 
#define  eSI_reg 143 
#define  eSP_reg 142 
#define  es_reg 141 
#define  fs_reg 140 
#define  gs_reg 139 
 int /*<<< orphan*/  mode_64bit ; 
 char** names16 ; 
 char** names32 ; 
 char** names64 ; 
 char** names8 ; 
 char** names8rex ; 
 char** names_seg ; 
 int /*<<< orphan*/  oappend (char const*) ; 
 int prefixes ; 
#define  rAX_reg 138 
#define  rBP_reg 137 
#define  rBX_reg 136 
#define  rCX_reg 135 
#define  rDI_reg 134 
#define  rDX_reg 133 
#define  rSI_reg 132 
#define  rSP_reg 131 
 int rex ; 
#define  si_reg 130 
#define  sp_reg 129 
#define  ss_reg 128 
 int used_prefixes ; 

__attribute__((used)) static void
OP_REG (int code, int sizeflag)
{
  const char *s;
  int add = 0;
  USED_REX (REX_B);
  if (rex & REX_B)
    add = 8;

  switch (code)
    {
    case ax_reg: case cx_reg: case dx_reg: case bx_reg:
    case sp_reg: case bp_reg: case si_reg: case di_reg:
      s = names16[code - ax_reg + add];
      break;
    case es_reg: case ss_reg: case cs_reg:
    case ds_reg: case fs_reg: case gs_reg:
      s = names_seg[code - es_reg + add];
      break;
    case al_reg: case ah_reg: case cl_reg: case ch_reg:
    case dl_reg: case dh_reg: case bl_reg: case bh_reg:
      USED_REX (0);
      if (rex)
	s = names8rex[code - al_reg + add];
      else
	s = names8[code - al_reg];
      break;
    case rAX_reg: case rCX_reg: case rDX_reg: case rBX_reg:
    case rSP_reg: case rBP_reg: case rSI_reg: case rDI_reg:
      if (address_mode == mode_64bit && (sizeflag & DFLAG))
	{
	  s = names64[code - rAX_reg + add];
	  break;
	}
      code += eAX_reg - rAX_reg;
      /* Fall through.  */
    case eAX_reg: case eCX_reg: case eDX_reg: case eBX_reg:
    case eSP_reg: case eBP_reg: case eSI_reg: case eDI_reg:
      USED_REX (REX_W);
      if (rex & REX_W)
	s = names64[code - eAX_reg + add];
      else if (sizeflag & DFLAG)
	s = names32[code - eAX_reg + add];
      else
	s = names16[code - eAX_reg + add];
      used_prefixes |= (prefixes & PREFIX_DATA);
      break;
    default:
      s = INTERNAL_DISASSEMBLER_ERROR;
      break;
    }
  oappend (s);
}