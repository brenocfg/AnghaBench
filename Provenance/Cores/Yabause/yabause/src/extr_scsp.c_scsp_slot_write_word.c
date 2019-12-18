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
struct TYPE_2__ {int kb; int sbctl; int ssctl; int lpctl; int pcm8b; int sa; int lsa; int lea; int d2r; int d1r; int hold; int ar; int unknown1; int ls; int krs; int dl; int rr; int unknown2; int si; int sd; int tl; int mdl; int mdxsl; int mdysl; int unknown3; int unknown4; int oct; int fns; int re; int lfof; int plfows; int plfos; int alfows; int alfos; int unknown5; int isel; int imxl; int disdl; int dipan; int efsdl; int efpan; } ;
struct Slot {TYPE_1__ regs; } ;
struct Scsp {struct Slot* slots; } ;

/* Variables and functions */
 int /*<<< orphan*/  keyonex (struct Scsp*) ; 

void scsp_slot_write_word(struct Scsp *s, u32 addr, u16 data)
{
   int slot_num = (addr >> 5) & 0x1f;
   struct Slot * slot = &s->slots[slot_num];
   u32 offset = (addr - (0x20 * slot_num));

   switch (offset >> 1)
   {
   case 0:
      slot->regs.kb = (data >> 11) & 1;//has to be done before keyonex

      if (data & (1 << 12))
         keyonex(s);

      slot->regs.sbctl = (data >> 9) & 3;
      slot->regs.ssctl = (data >> 7) & 3;
      slot->regs.lpctl = (data >> 5) & 3;
      slot->regs.pcm8b = (data >> 4) & 1;
      slot->regs.sa = (slot->regs.sa & 0xffff) | ((data & 0xf) << 16);
      break;
   case 1:
      slot->regs.sa = (slot->regs.sa & 0xf0000) | data;
      break;
   case 2:
      slot->regs.lsa = data;
      break;
   case 3:
      slot->regs.lea = data;
      break;
   case 4:
      slot->regs.d2r = data >> 11;
      slot->regs.d1r = (data >> 6) & 0x1f;
      slot->regs.hold = (data >> 5) & 1;
      slot->regs.ar = data & 0x1f;
      break;
   case 5:
      slot->regs.unknown1 = (data >> 15) & 1;
      slot->regs.ls = (data >> 14) & 1;
      slot->regs.krs = (data >> 10) & 0xf;
      slot->regs.dl = (data >> 5) & 0x1f;
      slot->regs.rr = data & 0x1f;
      break;
   case 6:
      slot->regs.unknown2 = (data >> 10) & 3;
      slot->regs.si = (data >> 9) & 1;
      slot->regs.sd = (data >> 8) & 1;
      slot->regs.tl = data & 0xff;
      break;
   case 7:
      slot->regs.mdl = (data >> 12) & 0xf;
      slot->regs.mdxsl = (data >> 6) & 0x3f;
      slot->regs.mdysl = data & 0x3f;
      break;
   case 8:
      slot->regs.unknown3 = (data >> 15) & 1;
      slot->regs.unknown4 = (data >> 10) & 1;
      slot->regs.oct = (data >> 11) & 0xf;
      slot->regs.fns = data & 0x3ff;
      break;
   case 9:
      slot->regs.re = (data >> 15) & 1;
      slot->regs.lfof = (data >> 10) & 0x1f;
      slot->regs.plfows = (data >> 8) & 3;
      slot->regs.plfos = (data >> 5) & 7;
      slot->regs.alfows = (data >> 3) & 3;
      slot->regs.alfos = data & 7;
      break;
   case 10:
      slot->regs.unknown5 = (data >> 7) & 1;
      slot->regs.isel = (data >> 3) & 0xf;
      slot->regs.imxl = data & 7;
      break;
   case 11:
      slot->regs.disdl = (data >> 13) & 7;
      slot->regs.dipan = (data >> 8) & 0x1f;
      slot->regs.efsdl = (data >> 5) & 7;
      slot->regs.efpan = data & 0x1f;
      break;
   default:
      break;
   }
}