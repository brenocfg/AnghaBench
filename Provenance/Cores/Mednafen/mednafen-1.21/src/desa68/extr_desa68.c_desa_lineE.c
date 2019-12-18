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
typedef  char u16 ;
struct TYPE_2__ {int opsz; int reg9; int adrmode0; int w; char reg0; char szchar; int /*<<< orphan*/  mode3; } ;

/* Variables and functions */
 TYPE_1__ d ; 
 int /*<<< orphan*/  desa_ascii (char) ; 
 int /*<<< orphan*/  desa_char (char) ; 
 int /*<<< orphan*/  desa_dcw () ; 
 int /*<<< orphan*/  get_ea_2 (int /*<<< orphan*/ ,char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void desa_lineE(void)
{
  static u16 shf_ascii[4] = { 'AS', 'LS', 'RO', 'RO' };

  /* Memory */
  if(d.opsz==3)
    {
      const int modemsk = 00774;
      int type = d.reg9;
      if (!(modemsk & (1<<d.adrmode0)) || (type&4)) {
	desa_dcw();
	return;
      }
      desa_ascii(shf_ascii[type]);
      desa_char ((d.w&0400) ? 'L' :'R');
      if(type==2) desa_char('X');
      desa_char (' ');
      get_ea_2(d.mode3, d.reg0, 0);
    }

  /* Register */
  else
    {
      int type = (d.w>>3)&3;
      desa_ascii (shf_ascii[type]);
      desa_char ((d.w&0400) ? 'L' :'R');
      if(type==2) desa_char('X');
      desa_ascii(d.szchar);
      /* dn,dn */
      if(d.w&(1<<5))
	desa_ascii(' D0'+d.reg9);
      /* #x,dn */
      else
	desa_ascii(' #1'+((d.reg9-1)&7));
      desa_ascii(',D0'+d.reg0);
    }
}