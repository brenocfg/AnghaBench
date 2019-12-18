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
struct SiS_Private {int /*<<< orphan*/  SiS_Part4Port; } ;

/* Variables and functions */
 int /*<<< orphan*/  SiS_DDC2Delay (struct SiS_Private*,int) ; 
 int SiS_GetReg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SiS_SetRegOR (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SiS_WaitVBRetrace (struct SiS_Private*) ; 

void
SiS_SiS30xBLOn(struct SiS_Private *SiS_Pr)
{
  /* Switch on LCD backlight on SiS30xLV */
  SiS_DDC2Delay(SiS_Pr,0xff00);
  if(!(SiS_GetReg(SiS_Pr->SiS_Part4Port,0x26) & 0x02)) {
     SiS_SetRegOR(SiS_Pr->SiS_Part4Port,0x26,0x02);
     SiS_WaitVBRetrace(SiS_Pr);
  }
  if(!(SiS_GetReg(SiS_Pr->SiS_Part4Port,0x26) & 0x01)) {
     SiS_SetRegOR(SiS_Pr->SiS_Part4Port,0x26,0x01);
  }
}