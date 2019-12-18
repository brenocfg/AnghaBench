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
struct SiS_Private {int SiS_DDC_Index; int SiS_DDC_Data; int SiS_DDC_Clk; int SiS_DDC_DeviceAddr; unsigned short SiS_DDC_ReadAddr; } ;

/* Variables and functions */
 unsigned short SiS_GetChReg (struct SiS_Private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SiS_SetupDDCN (struct SiS_Private*) ; 

unsigned short
SiS_GetCH701x(struct SiS_Private *SiS_Pr, unsigned short tempbx)
{
  SiS_Pr->SiS_DDC_Index = 0x11;			/* Bit 0 = SC;  Bit 1 = SD */
  SiS_Pr->SiS_DDC_Data  = 0x08;			/* Bitmask in IndexReg for Data */
  SiS_Pr->SiS_DDC_Clk   = 0x04;			/* Bitmask in IndexReg for Clk */
  SiS_SetupDDCN(SiS_Pr);
  SiS_Pr->SiS_DDC_DeviceAddr = 0xEA;		/* DAB */

  SiS_Pr->SiS_DDC_ReadAddr = tempbx;

  return SiS_GetChReg(SiS_Pr,0);
}