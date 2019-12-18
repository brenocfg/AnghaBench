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
struct SiS_Private {scalar_t__ SiS_ModeType; int /*<<< orphan*/  SiS_P3ce; TYPE_1__* SiS_StandTable; } ;
struct TYPE_2__ {unsigned char* GRC; } ;

/* Variables and functions */
 scalar_t__ ModeVGA ; 
 int /*<<< orphan*/  SiS_SetReg (int /*<<< orphan*/ ,unsigned short,unsigned char) ; 
 int /*<<< orphan*/  SiS_SetRegAND (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
SiS_SetGRCRegs(struct SiS_Private *SiS_Pr, unsigned short StandTableIndex)
{
   unsigned char  GRdata;
   unsigned short i;

   for(i = 0; i <= 0x08; i++) {
      GRdata = SiS_Pr->SiS_StandTable[StandTableIndex].GRC[i];
      SiS_SetReg(SiS_Pr->SiS_P3ce,i,GRdata);
   }

   if(SiS_Pr->SiS_ModeType > ModeVGA) {
      /* 256 color disable */
      SiS_SetRegAND(SiS_Pr->SiS_P3ce,0x05,0xBF);
   }
}