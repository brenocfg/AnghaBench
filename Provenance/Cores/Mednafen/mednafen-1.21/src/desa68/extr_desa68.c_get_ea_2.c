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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  void* s8 ;
typedef  int s32 ;
typedef  int s16 ;
struct TYPE_2__ {void* w; int ea; int flags; int /*<<< orphan*/  pc; } ;

/* Variables and functions */
 int DESA68_SYMBOL_FLAG ; 
#define  MODE_ABSL 139 
#define  MODE_ABSW 138 
#define  MODE_AN 137 
#define  MODE_ANp 136 
#define  MODE_DN 135 
#define  MODE_IMM 134 
#define  MODE_dAN 133 
#define  MODE_dANXI 132 
#define  MODE_dPC 131 
#define  MODE_dPCXI 130 
#define  MODE_iAN 129 
#define  MODE_pAN 128 
 int adrL () ; 
 int adrW () ; 
 TYPE_1__ d ; 
 int /*<<< orphan*/  desa_absL (int) ; 
 int /*<<< orphan*/  desa_ascii (int) ; 
 int /*<<< orphan*/  desa_char (char) ; 
 int /*<<< orphan*/  desa_immL (int) ; 
 int /*<<< orphan*/  desa_label (int) ; 
 int /*<<< orphan*/  desa_signifiant (void*) ; 
 int /*<<< orphan*/  desa_str (char*) ; 
 int /*<<< orphan*/  desa_usignifiant (int) ; 
 int /*<<< orphan*/  immB () ; 
 int /*<<< orphan*/  immL () ; 
 int /*<<< orphan*/  immW () ; 
 int indAnXi () ; 
 int /*<<< orphan*/  read_pc () ; 
 int relPC () ; 
 int /*<<< orphan*/  update_ea (int) ; 

__attribute__((used)) static void get_ea_2(u32 mode, u32 reg, u8 sz)
{
  s32 v;

  if(mode==MODE_ABSW) {
    mode += reg;
  }

  switch(mode )
    {
    case MODE_DN:
      desa_ascii('D0'+reg);
      break;
    case MODE_AN:
      desa_ascii('A0'+reg);
      break;
    case MODE_iAN:
      desa_ascii('(A0)'+(reg<<8));
      break;
    case MODE_pAN:
      desa_char('-');
      desa_ascii('(A0)'+(reg<<8));
      break;
    case MODE_ANp:
      desa_ascii('(A0)'+(reg<<8));
      desa_char('+');
      break;
    case MODE_dAN:
      read_pc();
      desa_signifiant(d.w);
      desa_ascii('(A0)'+(reg<<8));
      break;
    case MODE_dANXI:
      v = indAnXi();
      d.ea = (s8)(v>>8);
      desa_signifiant((s8)(v>>8));
      desa_ascii('(A0,'+(reg<<8));
      v = (v&0xFFFF00FF)+('.'<<8);
      desa_ascii(v);
      desa_char(')');
      break;
    case MODE_ABSW:
      d.ea = v = adrW();
      desa_usignifiant(v);
      desa_ascii('.W');
      break;
    case MODE_ABSL:
      d.ea = v = adrL();
      update_ea(v);
      desa_absL(v);
      break;
    case MODE_dPC:
      d.ea = v = relPC();
      update_ea(v);
      if (d.flags & DESA68_SYMBOL_FLAG) {
	desa_label(v);
      } else {
	desa_usignifiant(v);
      }
      desa_str("(PC)");
      break;
    case MODE_dPCXI:
      v = indAnXi();
      d.ea = d.pc-2+(s8)(v>>8);
      update_ea(d.ea);
      if (d.flags & DESA68_SYMBOL_FLAG) {
	desa_label(d.ea);
      } else {
	desa_usignifiant(d.ea);
      }
      desa_str("(PC,");
      v = (v&0xFFFF00FF)+('.'<<8);
      desa_ascii(v);
      desa_char(')');
      break;
    case MODE_IMM:
      switch(sz )
	{
	case 1:
	case 'B':
	  v = (s8)immB();
	  desa_immL(v);
	  break;
	case 2:
	case 'W':
	  v = (s16)immW();
	  desa_immL(v);
	  break;
	case 4:
	case 'L':
	  v = (u32)immL();
	  desa_immL(v);
	  return;
	default:
	  desa_str("#");
	  /*BREAKPOINT68;*/
	  break;
	}
      break;
    default:
      desa_char('?');
      desa_usignifiant(mode);
      desa_char('?');
      break;
    }
}