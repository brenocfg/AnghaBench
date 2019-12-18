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
struct TYPE_2__ {int w; int adrmode0; int mode3; int reg0; } ;

/* Variables and functions */
 int MODE_pAN ; 
 TYPE_1__ d ; 
 int /*<<< orphan*/  desa_ascii (char) ; 
 int /*<<< orphan*/  desa_char (char) ; 
 int /*<<< orphan*/  get_ea_2 (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_movemreg (int,int) ; 
 int immW () ; 

__attribute__((used)) static int check_desa_movem()
{
  int modemsk, regmsk;
  int mode3, reg0, w;
  if((d.w&05600)!=04200)
    return 0;
  modemsk = !(d.w&02000) ? 00764 : 03754;
  if(!(modemsk&(1<<d.adrmode0)))
    return 0;

  desa_ascii('MOVE');
  desa_ascii('M.');
  desa_char (!(d.w&0100)?'W':'L');
  desa_char (' ');

  w = d.w;
  mode3 = d.mode3;
  reg0 = d.reg0;
  regmsk = immW();

  /*  -> reg */
  if(w&02000)
    {
      get_ea_2(mode3, reg0, 0);
      desa_char(',');
      get_movemreg(regmsk,0);
    }
  /* -> mem */
  else
    {
      get_movemreg(regmsk, (mode3==MODE_pAN) ? 15 : 0);
      desa_char(',');
      get_ea_2(mode3, reg0, 0);
    }
  return 1;
}