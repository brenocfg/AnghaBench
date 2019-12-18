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
typedef  int u16 ;
struct TYPE_2__ {int kb; int sbctl; int ssctl; int lpctl; int pcm8b; int sa; int lsa; int lea; int d2r; int d1r; int hold; int ar; int unknown1; int ls; int krs; int dl; int rr; int unknown2; int si; int sd; int tl; int mdl; int mdxsl; int mdysl; int unknown3; int oct; int unknown4; int fns; int re; int lfof; int plfows; int plfos; int alfows; int alfos; int unknown5; int isel; int imxl; int disdl; int dipan; int efsdl; int efpan; } ;
struct Slot {TYPE_1__ regs; } ;
struct Scsp {struct Slot* slots; } ;

/* Variables and functions */

u16 scsp_slot_read_word(struct Scsp *s, u32 addr)
{
   int slot_num = (addr >> 5) & 0x1f;
   struct Slot * slot = &s->slots[slot_num];
   u32 offset = (addr - (0x20 * slot_num));
   u16 data = 0;

   switch (offset >> 1)
   {
   case 0:
      //keyonex not stored
      data |= slot->regs.kb << 11;
      data |= slot->regs.sbctl << 9;
      data |= slot->regs.ssctl << 7;
      data |= slot->regs.lpctl << 5;
      data |= slot->regs.pcm8b << 4;
      data |= (slot->regs.sa >> 16) & 0xf;
      break;
   case 1:
      data = slot->regs.sa & 0xffff;
      break;
   case 2:
      data = slot->regs.lsa;
      break;
   case 3:
      data = slot->regs.lea;
      break;
   case 4:
      data |= slot->regs.d2r << 11;
      data |= slot->regs.d1r << 6;
      data |= slot->regs.hold << 5;
      data |= slot->regs.ar;
      break;
   case 5:
      data |= slot->regs.unknown1 << 15;
      data |= slot->regs.ls << 14;
      data |= slot->regs.krs << 10;
      data |= slot->regs.dl << 5;
      data |= slot->regs.rr;
      break;
   case 6:
      data |= slot->regs.unknown2 << 10;
      data |= slot->regs.si << 9;
      data |= slot->regs.sd << 8;
      data |= slot->regs.tl;
      break;
   case 7:
      data |= slot->regs.mdl << 12;
      data |= slot->regs.mdxsl << 6;
      data |= slot->regs.mdysl;
      break;
   case 8:
      data |= slot->regs.unknown3 << 15;
      data |= slot->regs.oct << 11;
      data |= slot->regs.unknown4 << 10;
      data |= slot->regs.fns;
      break;
   case 9:
      data |= slot->regs.re << 15;
      data |= slot->regs.lfof << 10;
      data |= slot->regs.plfows << 8;
      data |= slot->regs.plfos << 5;
      data |= slot->regs.alfows << 3;
      data |= slot->regs.alfos;
      break;
   case 10:
      data |= slot->regs.unknown5 << 7;
      data |= slot->regs.isel << 3;
      data |= slot->regs.imxl;
      break;
   case 11:
      data |= slot->regs.disdl << 13;
      data |= slot->regs.dipan << 8;
      data |= slot->regs.efsdl << 5;
      data |= slot->regs.efpan;
      break;
   }
   return data;
}