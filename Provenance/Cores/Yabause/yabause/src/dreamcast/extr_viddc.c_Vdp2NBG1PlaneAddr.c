#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int planeh; int planew; int patterndatasize; int patternwh; int addr; } ;
typedef  TYPE_1__ vdp2draw_struct ;
typedef  int u32 ;
struct TYPE_5__ {int MPOFN; int MPABN1; int MPCDN1; } ;

/* Variables and functions */
 TYPE_2__* Vdp2Regs ; 

__attribute__((used)) static void Vdp2NBG1PlaneAddr(vdp2draw_struct *info, int i)
{
   u32 offset = (Vdp2Regs->MPOFN & 0x70) << 2;
   u32 tmp=0;
   int deca;
   int multi;

   switch(i)
   {
      case 0:
         tmp = offset | (Vdp2Regs->MPABN1 & 0xFF);
         break;
      case 1:
         tmp = offset | (Vdp2Regs->MPABN1 >> 8);
         break;
      case 2:
         tmp = offset | (Vdp2Regs->MPCDN1 & 0xFF);
         break;
      case 3:
         tmp = offset | (Vdp2Regs->MPCDN1 >> 8);
         break;
   }

   deca = info->planeh + info->planew - 2;
   multi = info->planeh * info->planew;

   //if (Vdp2Regs->VRSIZE & 0x8000)
   //{
      if (info->patterndatasize == 1)
      {
         if (info->patternwh == 1)
            info->addr = ((tmp & 0x3F) >> deca) * (multi * 0x2000);
         else
            info->addr = (tmp >> deca) * (multi * 0x800);
      }
      else
      {
         if (info->patternwh == 1)
            info->addr = ((tmp & 0x1F) >> deca) * (multi * 0x4000);
         else
            info->addr = ((tmp & 0x7F) >> deca) * (multi * 0x1000);
      }
   /*}
   else
   {
      if (info->patterndatasize == 1)
      {
         if (info->patternwh == 1)
            info->addr = ((tmp & 0x1F) >> deca) * (multi * 0x2000);
         else
            info->addr = ((tmp & 0x7F) >> deca) * (multi * 0x800);
      }
      else
      {
         if (info->patternwh == 1)
            info->addr = ((tmp & 0xF) >> deca) * (multi * 0x4000);
         else
            info->addr = ((tmp & 0x3F) >> deca) * (multi * 0x1000);
      }
   }*/
}