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
struct TYPE_5__ {int /*<<< orphan*/  (* GetPC ) () ;int /*<<< orphan*/  (* GetSR ) () ;int /*<<< orphan*/  (* GetAReg ) (int) ;int /*<<< orphan*/  (* GetDReg ) (int) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  PC; int /*<<< orphan*/  SR; int /*<<< orphan*/ * A; int /*<<< orphan*/ * D; } ;
typedef  TYPE_1__ M68KRegs ;

/* Variables and functions */
 TYPE_3__* M68K ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  stub2 (int) ; 
 int /*<<< orphan*/  stub3 () ; 
 int /*<<< orphan*/  stub4 () ; 

void M68KGetRegisters(M68KRegs *regs)
{
   int i;

   if (regs != NULL)
   {
      for (i = 0; i < 8; i++)
      {
         regs->D[i] = M68K->GetDReg(i);
         regs->A[i] = M68K->GetAReg(i);
      }
      regs->SR = M68K->GetSR();
      regs->PC = M68K->GetPC();
   }
}