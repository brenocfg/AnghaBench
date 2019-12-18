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
struct SiS_Private {int /*<<< orphan*/  SiS_P3da; int /*<<< orphan*/  SiS_P3d4; int /*<<< orphan*/  SiS_P3c4; } ;

/* Variables and functions */
 int SiS_GetReg (int /*<<< orphan*/ ,int) ; 
 int SiS_GetRegByte (int /*<<< orphan*/ ) ; 

void
SiS_WaitRetrace1(struct SiS_Private *SiS_Pr)
{
   unsigned short watchdog;

   if(SiS_GetReg(SiS_Pr->SiS_P3c4,0x1f) & 0xc0) return;
   if(!(SiS_GetReg(SiS_Pr->SiS_P3d4,0x17) & 0x80)) return;

   watchdog = 65535;
   while((SiS_GetRegByte(SiS_Pr->SiS_P3da) & 0x08) && --watchdog);
   watchdog = 65535;
   while((!(SiS_GetRegByte(SiS_Pr->SiS_P3da) & 0x08)) && --watchdog);
}