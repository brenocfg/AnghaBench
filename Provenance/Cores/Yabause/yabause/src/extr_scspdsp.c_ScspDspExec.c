#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int ira; size_t iwa; int bsel; int tra; int xsel; int ysel; size_t coef; int shift; int twa; size_t masa; int table; size_t ewa; scalar_t__ ewt; scalar_t__ adrl; scalar_t__ mwt; scalar_t__ mrd; scalar_t__ nxadr; scalar_t__ adreb; scalar_t__ frcl; scalar_t__ twt; scalar_t__ yrl; scalar_t__ zero; scalar_t__ negb; scalar_t__ iwt; } ;
union ScspDspInstruction {TYPE_1__ part; int /*<<< orphan*/  all; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;
typedef  int s32 ;
struct TYPE_7__ {int /*<<< orphan*/ * mpro; } ;
struct TYPE_6__ {int inputs; int* mems; int* mixs; int* exts; int mrd_value; int* temp; int mdec_ct; int b; int acc; int x; int y; int frc_reg; int* coef; int y_reg; int shifted; int* madrs; int adrs_reg; int rbl; int rbp; int* efreg; } ;
typedef  TYPE_2__ ScspDsp ;

/* Variables and functions */
 int float_to_int (int) ; 
 int int_to_float (int) ; 
 void* saturate_24 (int) ; 
 TYPE_3__ scsp_dsp ; 

void ScspDspExec(ScspDsp* dsp, int addr, u8 * sound_ram)
{
   u16* sound_ram_16 = (u16*)sound_ram;
   u64 mul_temp = 0;

   union ScspDspInstruction instruction;
   instruction.all = scsp_dsp.mpro[addr];

   if (instruction.part.ira >= 0 && instruction.part.ira <= 0x1f)
      dsp->inputs = dsp->mems[instruction.part.ira & 0x1f];
   else if (instruction.part.ira >= 0x20 && instruction.part.ira <= 0x2f)
      dsp->inputs = dsp->mixs[instruction.part.ira - 0x20] << 4;
   else if (instruction.part.ira == 0x30 || instruction.part.ira == 0x31)
      dsp->inputs = dsp->exts[(instruction.part.ira - 0x30) & 1];

   if (instruction.part.iwt)
      dsp->mems[instruction.part.iwa] = dsp->mrd_value;

   if (instruction.part.bsel == 0)
   {
      s32 temp_val = dsp->temp[(instruction.part.tra + dsp->mdec_ct) & 0x7f];

      if (temp_val & 0x800000)
         temp_val |= 0x3000000;//sign extend to 26 bits

      dsp->b = temp_val;
   }
   else if (instruction.part.bsel == 1)
      dsp->b = dsp->acc;

   if (instruction.part.negb)
      dsp->b = 0 - dsp->b;

   if (instruction.part.zero)
      dsp->b = 0;

   if (instruction.part.xsel == 0)
      dsp->x = dsp->temp[(instruction.part.tra + dsp->mdec_ct) & 0x7f];
   else if (instruction.part.xsel == 1)
      dsp->x = dsp->inputs;

   if (instruction.part.ysel == 0)
      dsp->y = dsp->frc_reg;
   else if (instruction.part.ysel == 1)
   {
      dsp->y = dsp->coef[instruction.part.coef] >> 3;

      if (dsp->coef[instruction.part.coef] & 0x8000)
         dsp->y |= 0xE000;
   }
   else if (instruction.part.ysel == 2)
      dsp->y = (dsp->y_reg >> 11) & 0x1FFF;
   else if (instruction.part.ysel == 3)
      dsp->y = (dsp->y_reg >> 4) & 0xFFF;

   if (instruction.part.yrl)
      dsp->y_reg = dsp->inputs;

   if (instruction.part.shift == 0)
      dsp->shifted = saturate_24(dsp->acc);
   else if (instruction.part.shift == 1)
      dsp->shifted = saturate_24(dsp->acc * 2);
   else if (instruction.part.shift == 2)
      dsp->shifted = (dsp->acc * 2) & 0xffffff;
   else if (instruction.part.shift == 2)
      dsp->shifted = dsp->acc & 0xffffff;

   mul_temp = (u64)dsp->x * (u64)dsp->y;//prevent clipping
   dsp->acc = (mul_temp >> 12) + dsp->b;

   dsp->acc &= 0xffffff;

   if (dsp->acc & 0x800000)
      dsp->acc |= 0xff000000;

   if (instruction.part.twt)
      dsp->temp[(instruction.part.twa + dsp->mdec_ct) & 0x7f] = dsp->shifted;

   if (instruction.part.frcl)
   {
      if (instruction.part.shift == 3)
         dsp->frc_reg = dsp->shifted & 0xFFF;
      else
         dsp->frc_reg = (dsp->shifted >> 11) & 0x1FFF;
   }

   if (instruction.part.mrd || instruction.part.mwt)
   {
      u32 address = dsp->madrs[instruction.part.masa];

      if (instruction.part.table == 0)
         address += dsp->mdec_ct;

      if (instruction.part.adreb)
         address += dsp->adrs_reg & 0xfff;

      if (instruction.part.nxadr)
         address += 1;

      if (instruction.part.table == 0)
      {
         if (dsp->rbl == 0)
            address &= 0x1fff;
         else if (dsp->rbl == 1)
            address &= 0x3fff;
         else if (dsp->rbl == 2)
            address &= 0x7fff;
         else if (dsp->rbl == 3)
            address &= 0xffff;
      }
      else if (instruction.part.table == 1)
         address &= 0xffff;

      address += (dsp->rbp << 11) * 2;

      if (instruction.part.mrd)
      {
         u16 temp = sound_ram_16[address & 0x7ffff];
         dsp->mrd_value = float_to_int(temp);
      }

      if (instruction.part.mwt)
      {
         s32 shifted_val = dsp->shifted;
         shifted_val = int_to_float(shifted_val);
         sound_ram_16[address & 0x7ffff] = shifted_val;
      }
   }

   if (instruction.part.adrl)
   {
      if (instruction.part.shift == 3)
         dsp->adrs_reg = dsp->inputs >> 16;
      else
         dsp->adrs_reg = (dsp->shifted >> 12) & 0xFFF;
   }

   if (instruction.part.ewt)
      dsp->efreg[instruction.part.ewa] = dsp->shifted >> 8;
}