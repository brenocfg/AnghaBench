#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {int /*<<< orphan*/  EXLE; int /*<<< orphan*/  IOSEL; scalar_t__ DDR; scalar_t__ PDR; int /*<<< orphan*/  SF; int /*<<< orphan*/  SR; scalar_t__ OREG; int /*<<< orphan*/  COMREG; scalar_t__ IREG; } ;
struct TYPE_4__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  SmpcInternal ;
typedef  TYPE_1__ IOCheck_struct ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
 scalar_t__ SmpcInternalVars ; 
 TYPE_3__* SmpcRegs ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yread (TYPE_1__*,void*,int,int,int /*<<< orphan*/ *) ; 

int SmpcLoadState(FILE *fp, int version, int size)
{
   IOCheck_struct check = { 0, 0 };
   int internalsizev2 = sizeof(SmpcInternal) - 8;

   // Read registers
   yread(&check, (void *)SmpcRegs->IREG, sizeof(u8), 7, fp);
   yread(&check, (void *)&SmpcRegs->COMREG, sizeof(u8), 1, fp);
   yread(&check, (void *)SmpcRegs->OREG, sizeof(u8), 32, fp);
   yread(&check, (void *)&SmpcRegs->SR, sizeof(u8), 1, fp);
   yread(&check, (void *)&SmpcRegs->SF, sizeof(u8), 1, fp);
   yread(&check, (void *)SmpcRegs->PDR, sizeof(u8), 2, fp);
   yread(&check, (void *)SmpcRegs->DDR, sizeof(u8), 2, fp);
   yread(&check, (void *)&SmpcRegs->IOSEL, sizeof(u8), 1, fp);
   yread(&check, (void *)&SmpcRegs->EXLE, sizeof(u8), 1, fp);

   // Read internal variables
   if (version == 1)
   {
      // This handles the problem caused by the version not being incremented
      // when SmpcInternal was changed
      if ((size - 48) == internalsizev2)
         yread(&check, (void *)SmpcInternalVars, internalsizev2, 1, fp);
      else if ((size - 48) == 24)
         yread(&check, (void *)SmpcInternalVars, 24, 1, fp);
      else
         fseek(fp, size - 48, SEEK_CUR);
   }
   else if (version == 2)
      yread(&check, (void *)SmpcInternalVars, internalsizev2, 1, fp);
   else
      yread(&check, (void *)SmpcInternalVars, sizeof(SmpcInternal), 1, fp);

   // Read ID's of currently emulated peripherals(fix me)

   return size;
}