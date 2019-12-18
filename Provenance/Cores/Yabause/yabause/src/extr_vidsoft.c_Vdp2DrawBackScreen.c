#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  (* PostPixelFetchCalc ) (TYPE_1__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ vdp2draw_struct ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_8__ {int TVMD; int VRSIZE; int BKTAU; int BKTAL; } ;

/* Variables and functions */
 int /*<<< orphan*/  COLSAT2YAB16 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COLSAT2YAB32 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReadVdp2ColorOffset (TYPE_4__*,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T1ReadWord (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TitanPutBackHLine (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Vdp2Ram ; 
 TYPE_4__* Vdp2Regs ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int vdp2height ; 

__attribute__((used)) static void Vdp2DrawBackScreen(void)
{
   int i, j;

   // Only draw black if TVMD's DISP and BDCLMD bits are cleared
   if ((Vdp2Regs->TVMD & 0x8000) == 0 && (Vdp2Regs->TVMD & 0x100) == 0)
   {
      // Draw Black
      for (j = 0; j < vdp2height; j++)
         TitanPutBackHLine(j, COLSAT2YAB32(0x3F, 0));
   }
   else
   {
      // Draw Back Screen
      u32 scrAddr;
      u16 dot;
      vdp2draw_struct info = { 0 };

      ReadVdp2ColorOffset(Vdp2Regs, &info, (1 << 5), 0);

      if (Vdp2Regs->VRSIZE & 0x8000)
         scrAddr = (((Vdp2Regs->BKTAU & 0x7) << 16) | Vdp2Regs->BKTAL) * 2;
      else
         scrAddr = (((Vdp2Regs->BKTAU & 0x3) << 16) | Vdp2Regs->BKTAL) * 2;

      if (Vdp2Regs->BKTAU & 0x8000)
      {
         // Per Line
         for (i = 0; i < vdp2height; i++)
         {
            dot = T1ReadWord(Vdp2Ram, scrAddr);
            scrAddr += 2;

            TitanPutBackHLine(i, info.PostPixelFetchCalc(&info, COLSAT2YAB16(0x3f, dot)));
         }
      }
      else
      {
         // Single Color
         dot = T1ReadWord(Vdp2Ram, scrAddr);

         for (j = 0; j < vdp2height; j++)
            TitanPutBackHLine(j, info.PostPixelFetchCalc(&info, COLSAT2YAB16(0x3f, dot)));
      }
   }
}