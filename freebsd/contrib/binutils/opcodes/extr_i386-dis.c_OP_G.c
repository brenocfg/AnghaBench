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
struct TYPE_2__ {int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int DFLAG ; 
 int /*<<< orphan*/  INTERNAL_DISASSEMBLER_ERROR ; 
 int PREFIX_DATA ; 
 int REX_R ; 
 int REX_W ; 
 int /*<<< orphan*/  USED_REX (int) ; 
 int /*<<< orphan*/  address_mode ; 
#define  b_mode 137 
#define  d_mode 136 
#define  dq_mode 135 
#define  dqb_mode 134 
#define  dqd_mode 133 
#define  dqw_mode 132 
#define  m_mode 131 
 int /*<<< orphan*/  mode_64bit ; 
 TYPE_1__ modrm ; 
 int /*<<< orphan*/ * names16 ; 
 int /*<<< orphan*/ * names32 ; 
 int /*<<< orphan*/ * names64 ; 
 int /*<<< orphan*/ * names8 ; 
 int /*<<< orphan*/ * names8rex ; 
 int /*<<< orphan*/  oappend (int /*<<< orphan*/ ) ; 
 int prefixes ; 
#define  q_mode 130 
 int rex ; 
 int used_prefixes ; 
#define  v_mode 129 
#define  w_mode 128 

__attribute__((used)) static void
OP_G (int bytemode, int sizeflag)
{
  int add = 0;
  USED_REX (REX_R);
  if (rex & REX_R)
    add += 8;
  switch (bytemode)
    {
    case b_mode:
      USED_REX (0);
      if (rex)
	oappend (names8rex[modrm.reg + add]);
      else
	oappend (names8[modrm.reg + add]);
      break;
    case w_mode:
      oappend (names16[modrm.reg + add]);
      break;
    case d_mode:
      oappend (names32[modrm.reg + add]);
      break;
    case q_mode:
      oappend (names64[modrm.reg + add]);
      break;
    case v_mode:
    case dq_mode:
    case dqb_mode:
    case dqd_mode:
    case dqw_mode:
      USED_REX (REX_W);
      if (rex & REX_W)
	oappend (names64[modrm.reg + add]);
      else if ((sizeflag & DFLAG) || bytemode != v_mode)
	oappend (names32[modrm.reg + add]);
      else
	oappend (names16[modrm.reg + add]);
      used_prefixes |= (prefixes & PREFIX_DATA);
      break;
    case m_mode:
      if (address_mode == mode_64bit)
	oappend (names64[modrm.reg + add]);
      else
	oappend (names32[modrm.reg + add]);
      break;
    default:
      oappend (INTERNAL_DISASSEMBLER_ERROR);
      break;
    }
}