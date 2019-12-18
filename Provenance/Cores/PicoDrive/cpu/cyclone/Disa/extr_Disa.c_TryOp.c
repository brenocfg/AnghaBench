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
 int /*<<< orphan*/  Disa4E70 (int) ; 
 int /*<<< orphan*/  DisaAbcd (int) ; 
 int /*<<< orphan*/  DisaAddq (int) ; 
 int /*<<< orphan*/  DisaAddx (int) ; 
 int /*<<< orphan*/  DisaArithImm (int) ; 
 int /*<<< orphan*/  DisaArithReg (int) ; 
 int /*<<< orphan*/  DisaArithSr (int) ; 
 int /*<<< orphan*/  DisaAritha (int) ; 
 int /*<<< orphan*/  DisaAsr (int) ; 
 int /*<<< orphan*/  DisaAsrEa (int) ; 
 int /*<<< orphan*/  DisaBranch (int) ; 
 int /*<<< orphan*/  DisaBtstImm (int) ; 
 int /*<<< orphan*/  DisaBtstReg (int) ; 
 int /*<<< orphan*/  DisaCmpEor (int) ; 
 int /*<<< orphan*/  DisaCmpm (int) ; 
 int /*<<< orphan*/  DisaDbra (int) ; 
 int /*<<< orphan*/  DisaExg (int) ; 
 int /*<<< orphan*/  DisaExt (int) ; 
 int /*<<< orphan*/  DisaJsr (int) ; 
 int /*<<< orphan*/  DisaLea (int) ; 
 int /*<<< orphan*/  DisaLink (int) ; 
 int /*<<< orphan*/  DisaMove (int) ; 
 int /*<<< orphan*/  DisaMoveSr (int) ; 
 int /*<<< orphan*/  DisaMoveUsp (int) ; 
 int /*<<< orphan*/  DisaMovem (int) ; 
 int /*<<< orphan*/  DisaMovep (int) ; 
 int /*<<< orphan*/  DisaMoveq (int) ; 
 int /*<<< orphan*/  DisaMul (int) ; 
 int /*<<< orphan*/  DisaNbcd (int) ; 
 int /*<<< orphan*/  DisaNeg (int) ; 
 int /*<<< orphan*/  DisaPea (int) ; 
 int /*<<< orphan*/  DisaSet (int) ; 
 int /*<<< orphan*/  DisaSwap (int) ; 
 int /*<<< orphan*/  DisaTas (int) ; 
 int /*<<< orphan*/  DisaTrap (int) ; 
 int /*<<< orphan*/  DisaTst (int) ; 
 int /*<<< orphan*/  DisaUnlk (int) ; 
 int /*<<< orphan*/  OpChk (int) ; 

__attribute__((used)) static int TryOp(int op)
{
  if ((op&0xf100)==0x0000) DisaArithImm(op); // Ori/And/Sub/Add/Eor/Cmp Immediate
  if ((op&0xf5bf)==0x003c) DisaArithSr(op); // Ori/Andi/Eori $nnnn,sr
  if ((op&0xf100)==0x0100) DisaBtstReg(op);
  if ((op&0xf138)==0x0108) DisaMovep(op);
  if ((op&0xff00)==0x0800) DisaBtstImm(op); // Btst/Bchg/Bclr/Bset
  if ((op&0xc000)==0x0000) DisaMove(op);
  if ((op&0xf900)==0x4000) DisaNeg(op); // Negx/Clr/Neg/Not
  if ((op&0xf140)==0x4100) OpChk(op);
  if ((op&0xf1c0)==0x41c0) DisaLea(op);
  if ((op&0xf9c0)==0x40c0) DisaMoveSr(op);
  if ((op&0xffc0)==0x4800) DisaNbcd(op);
  if ((op&0xfff8)==0x4840) DisaSwap(op);
  if ((op&0xffc0)==0x4840) DisaPea(op);
  if ((op&0xffb8)==0x4880) DisaExt(op);
  if ((op&0xfb80)==0x4880) DisaMovem(op);
  if ((op&0xff00)==0x4a00) DisaTst(op);
  if ((op&0xffc0)==0x4ac0) DisaTas(op);
  if ((op&0xfff0)==0x4e40) DisaTrap(op);
  if ((op&0xfff8)==0x4e50) DisaLink(op);
  if ((op&0xfff8)==0x4e58) DisaUnlk(op);
  if ((op&0xfff0)==0x4e60) DisaMoveUsp(op);
  if ((op&0xfff8)==0x4e70) Disa4E70(op);
  if ((op&0xff80)==0x4e80) DisaJsr(op);
  if ((op&0xf000)==0x5000) DisaAddq(op);
  if ((op&0xf0c0)==0x50c0) DisaSet(op);
  if ((op&0xf0f8)==0x50c8) DisaDbra(op);
  if ((op&0xf000)==0x6000) DisaBranch(op);
  if ((op&0xa000)==0x8000) DisaArithReg(op); // Or/Sub/And/Add
  if ((op&0xb1f0)==0x8100) DisaAbcd(op);
  if ((op&0xb130)==0x9100) DisaAddx(op);
  if ((op&0xb0c0)==0x80c0) DisaMul(op);
  if ((op&0xf100)==0x7000) DisaMoveq(op);
  if ((op&0x90c0)==0x90c0) DisaAritha(op);
  if ((op&0xf000)==0xb000) DisaCmpEor(op);
  if ((op&0xf138)==0xb108) DisaCmpm(op);
  if ((op&0xf130)==0xc100) DisaExg(op);
  if ((op&0xf000)==0xe000) DisaAsr(op);
  if ((op&0xf8c0)==0xe0c0) DisaAsrEa(op);

  // Unknown opcoode
  return 0;
}