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
typedef  char u32 ;
struct TYPE_2__ {int adrmode0; size_t opsz; int w; char reg9; int /*<<< orphan*/  reg0; int /*<<< orphan*/  mode3; } ;

/* Variables and functions */
 TYPE_1__ d ; 
 int /*<<< orphan*/  desa_ascii (char) ; 
 int /*<<< orphan*/  desa_char (char) ; 
 int /*<<< orphan*/  desa_usignifiant (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_ea_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  read_pc () ; 

__attribute__((used)) static int check_desa_bitop(void)
{
  static u32 fn[] = { 'BTST', 'BCHG', 'BCLR', 'BSET'};
  int modemsk = 00775;
  unsigned int inst;

  if(!(modemsk&(1<<d.adrmode0)))
    return 0;

  inst = fn[d.opsz];
  /* B... #x,<AE>*/
  if(!(d.w&0400))
    {
      if((d.w&0xF00)!=0x800)
	return 0;
      desa_ascii(inst);
      desa_ascii(' #');
      read_pc();
      desa_usignifiant((u8)d.w);
    }
  else
    /* B... dn,<AE>*/
    {
      desa_ascii(inst);
      desa_ascii(' D0'+d.reg9);
    }
  desa_char(',');
  get_ea_2(d.mode3, d.reg0, 'B');

  return 1;
}