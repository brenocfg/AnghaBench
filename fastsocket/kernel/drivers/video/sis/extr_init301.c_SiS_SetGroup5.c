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
struct SiS_Private {int SiS_VBInfo; scalar_t__ SiS_ModeType; int /*<<< orphan*/  SiS_P3c4; } ;

/* Variables and functions */
 int LoadDACFlag ; 
 scalar_t__ ModeVGA ; 
 int SetCRT2ToLCDA ; 
 int SetInSlaveMode ; 
 int /*<<< orphan*/  SiS_LoadDAC (struct SiS_Private*,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetRegOR (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
SiS_SetGroup5(struct SiS_Private *SiS_Pr, unsigned short ModeNo, unsigned short ModeIdIndex)
{

  if(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA)  return;

  if(SiS_Pr->SiS_ModeType == ModeVGA) {
     if(!(SiS_Pr->SiS_VBInfo & (SetInSlaveMode | LoadDACFlag))) {
        SiS_SetRegOR(SiS_Pr->SiS_P3c4,0x1E,0x20);
        SiS_LoadDAC(SiS_Pr, ModeNo, ModeIdIndex);
     }
  }
}