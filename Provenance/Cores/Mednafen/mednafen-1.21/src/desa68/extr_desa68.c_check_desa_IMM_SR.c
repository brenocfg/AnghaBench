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
typedef  int u32 ;
struct TYPE_2__ {int w; int mode6; } ;

/* Variables and functions */
 scalar_t__ MODE_ABSW ; 
 scalar_t__ MODE_IMM ; 
 TYPE_1__ d ; 
 int /*<<< orphan*/  desa_ascii (char) ; 
 int /*<<< orphan*/  desa_char (char) ; 
 int /*<<< orphan*/  get_ea_2 (scalar_t__,scalar_t__,char) ; 

__attribute__((used)) static int check_desa_IMM_SR(void)
{
  u32 modemsk = 1 + (1<<2) + (1<<10);
  int mode = (d.w>>8)&15, inst='ORI';

  if((d.w&0677)!=0074 || !(modemsk&(1<<mode)))
    return 0;

  switch(mode)
    {
    case 0xA: /* EORI */
      inst = 'EORI';
      break;
#if 0
    case 0x0: /* ORI */
      inst = 'ORI';
      break;
#endif
    case 0x2: /* ANDI */
      inst = 'ANDI';
      break;
    }
  desa_ascii(inst);
  desa_char(' ');
  get_ea_2(MODE_ABSW, MODE_IMM-MODE_ABSW, 'W');
  desa_ascii((d.mode6&1) ? ',SR' : ',CCR');
  return 1;
}