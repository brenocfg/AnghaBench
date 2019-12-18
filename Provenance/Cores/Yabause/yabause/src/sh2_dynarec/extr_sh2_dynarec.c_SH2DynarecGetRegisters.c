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
 int /*<<< orphan*/  SH2DynarecGetGBR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SH2DynarecGetMACH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SH2DynarecGetMACL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SH2DynarecGetPC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SH2DynarecGetPR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SH2DynarecGetSR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SH2DynarecGetVBR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  master_reg ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  slave_reg ; 

void SH2DynarecGetRegisters(SH2_struct *context, sh2regs_struct *regs)
{
  if(context==MSH2) 
    memcpy(&(regs->R), master_reg, 16*sizeof(int));
  else 
    memcpy(&(regs->R), slave_reg, 16*sizeof(int));
  regs->SR.all=SH2DynarecGetSR(context);
  regs->GBR=SH2DynarecGetGBR(context);
  regs->VBR=SH2DynarecGetVBR(context);
  regs->MACH=SH2DynarecGetMACH(context);
  regs->MACL=SH2DynarecGetMACL(context);
  regs->PR=SH2DynarecGetPR(context);
  regs->PC=SH2DynarecGetPC(context);
}