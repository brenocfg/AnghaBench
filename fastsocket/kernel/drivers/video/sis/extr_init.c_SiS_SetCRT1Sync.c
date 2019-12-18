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
struct SiS_Private {int CInfoFlag; int /*<<< orphan*/  SiS_P3c2; TYPE_1__* SiS_RefIndex; scalar_t__ UseCustomMode; } ;
struct TYPE_2__ {int Ext_InfoFlag; } ;

/* Variables and functions */
 int /*<<< orphan*/  SiS_SetRegByte (int /*<<< orphan*/ ,unsigned short) ; 

__attribute__((used)) static void
SiS_SetCRT1Sync(struct SiS_Private *SiS_Pr, unsigned short RRTI)
{
   unsigned short sync;

   if(SiS_Pr->UseCustomMode) {
      sync = SiS_Pr->CInfoFlag >> 8;
   } else {
      sync = SiS_Pr->SiS_RefIndex[RRTI].Ext_InfoFlag >> 8;
   }

   sync &= 0xC0;
   sync |= 0x2f;
   SiS_SetRegByte(SiS_Pr->SiS_P3c2,sync);
}