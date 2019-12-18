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
struct SiS_Private {int /*<<< orphan*/  SiS_P3d4; int /*<<< orphan*/  SiS_ROMNew; } ;

/* Variables and functions */
 scalar_t__ IS_SIS650 ; 
 scalar_t__ IS_SIS651 ; 
 scalar_t__ IS_SIS661741660760 ; 
 int /*<<< orphan*/  SiS_SetRegAND (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SiS_SetRegOR (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
SiS_OpenCRTC(struct SiS_Private *SiS_Pr)
{
   if(IS_SIS650) {
      SiS_SetRegAND(SiS_Pr->SiS_P3d4,0x51,0x1f);
      if(IS_SIS651) SiS_SetRegOR(SiS_Pr->SiS_P3d4,0x51,0x20);
      SiS_SetRegAND(SiS_Pr->SiS_P3d4,0x56,0xe7);
   } else if(IS_SIS661741660760) {
      SiS_SetRegAND(SiS_Pr->SiS_P3d4,0x61,0xf7);
      SiS_SetRegAND(SiS_Pr->SiS_P3d4,0x51,0x1f);
      SiS_SetRegAND(SiS_Pr->SiS_P3d4,0x56,0xe7);
      if(!SiS_Pr->SiS_ROMNew) {
	 SiS_SetRegAND(SiS_Pr->SiS_P3d4,0x3a,0xef);
      }
   }
}