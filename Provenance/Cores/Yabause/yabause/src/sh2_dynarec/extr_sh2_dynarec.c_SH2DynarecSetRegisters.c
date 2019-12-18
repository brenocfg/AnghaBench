#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  all; } ;
struct TYPE_5__ {int /*<<< orphan*/  PC; int /*<<< orphan*/  PR; int /*<<< orphan*/  MACL; int /*<<< orphan*/  MACH; int /*<<< orphan*/  VBR; int /*<<< orphan*/  GBR; TYPE_1__ SR; int /*<<< orphan*/  R; } ;
typedef  TYPE_2__ sh2regs_struct ;
typedef  int /*<<< orphan*/  SH2_struct ;

/* Variables and functions */
 int /*<<< orphan*/ * MSH2 ; 
 int /*<<< orphan*/  SH2DynarecSetGBR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SH2DynarecSetMACH (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SH2DynarecSetMACL (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SH2DynarecSetPC (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SH2DynarecSetPR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SH2DynarecSetSR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SH2DynarecSetVBR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  master_reg ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  slave_reg ; 

void SH2DynarecSetRegisters(SH2_struct *context, const sh2regs_struct *regs)
{
  if(context==MSH2) 
    memcpy(master_reg, &(regs->R), 16*sizeof(int));
  else 
    memcpy(slave_reg, &(regs->R), 16*sizeof(int));
  SH2DynarecSetSR(context, regs->SR.all);
  SH2DynarecSetGBR(context, regs->GBR);
  SH2DynarecSetVBR(context, regs->VBR);
  SH2DynarecSetMACH(context, regs->MACH);
  SH2DynarecSetMACL(context, regs->MACL);
  SH2DynarecSetPR(context, regs->PR);
  SH2DynarecSetPC(context, regs->PC);
}