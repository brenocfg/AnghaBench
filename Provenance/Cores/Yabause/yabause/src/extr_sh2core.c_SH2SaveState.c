#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  sh2regs_struct ;
typedef  int /*<<< orphan*/  interrupt_struct ;
struct TYPE_14__ {int /*<<< orphan*/  (* GetInterrupts ) (TYPE_2__*,scalar_t__) ;} ;
struct TYPE_13__ {int /*<<< orphan*/  IsSSH2Running; } ;
struct TYPE_12__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_10__ {int shift; } ;
struct TYPE_11__ {scalar_t__ isslave; int /*<<< orphan*/  instruction; int /*<<< orphan*/  isIdle; int /*<<< orphan*/  cycles; int /*<<< orphan*/  delay; scalar_t__ DataArray; scalar_t__ AddressArray; int /*<<< orphan*/  NumberOfInterrupts; scalar_t__ interrupts; TYPE_1__ frc; int /*<<< orphan*/  onchip; } ;
typedef  TYPE_2__ SH2_struct ;
typedef  int /*<<< orphan*/  Onchip_struct ;
typedef  TYPE_3__ IOCheck_struct ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MAX_INTERRUPTS ; 
 TYPE_9__* SH2Core ; 
 int /*<<< orphan*/  SH2GetRegisters (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int StateFinishHeader (int /*<<< orphan*/ *,int) ; 
 int StateWriteHeader (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,scalar_t__) ; 
 TYPE_5__ yabsys ; 
 int /*<<< orphan*/  ywrite (TYPE_3__*,void*,int,int,int /*<<< orphan*/ *) ; 

int SH2SaveState(SH2_struct *context, FILE *fp)
{
   int offset;
   IOCheck_struct check = { 0, 0 };
   sh2regs_struct regs;

   // Write header
   if (context->isslave == 0)
      offset = StateWriteHeader(fp, "MSH2", 1);
   else
   {
      offset = StateWriteHeader(fp, "SSH2", 1);
      ywrite(&check, (void *)&yabsys.IsSSH2Running, 1, 1, fp);
   }

   // Write registers
   SH2GetRegisters(context, &regs);
   ywrite(&check, (void *)&regs, sizeof(sh2regs_struct), 1, fp);

   // Write onchip registers
   ywrite(&check, (void *)&context->onchip, sizeof(Onchip_struct), 1, fp);

   // Write internal variables
   // FIXME: write the clock divisor rather than the shift amount for
   // backward compatibility (fix this next time the save state version
   // is updated)
   context->frc.shift = 1 << context->frc.shift;
   ywrite(&check, (void *)&context->frc, sizeof(context->frc), 1, fp);
   {
      u32 div = context->frc.shift;
      context->frc.shift = 0;
      while ((div >>= 1) != 0)
         context->frc.shift++;
   }
   context->NumberOfInterrupts = SH2Core->GetInterrupts(context, context->interrupts);
   ywrite(&check, (void *)context->interrupts, sizeof(interrupt_struct), MAX_INTERRUPTS, fp);
   ywrite(&check, (void *)&context->NumberOfInterrupts, sizeof(u32), 1, fp);
   ywrite(&check, (void *)context->AddressArray, sizeof(u32), 0x100, fp);
   ywrite(&check, (void *)context->DataArray, sizeof(u8), 0x1000, fp);
   ywrite(&check, (void *)&context->delay, sizeof(u32), 1, fp);
   ywrite(&check, (void *)&context->cycles, sizeof(u32), 1, fp);
   ywrite(&check, (void *)&context->isslave, sizeof(u8), 1, fp);
   ywrite(&check, (void *)&context->isIdle, sizeof(u8), 1, fp);
   ywrite(&check, (void *)&context->instruction, sizeof(u16), 1, fp);

   return StateFinishHeader(fp, offset);
}