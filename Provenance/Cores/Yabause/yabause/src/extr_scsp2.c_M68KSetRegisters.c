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
struct TYPE_5__ {int /*<<< orphan*/  (* SetPC ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* SetSR ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* SetAReg ) (int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* SetDReg ) (int,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  PC; int /*<<< orphan*/  SR; int /*<<< orphan*/ * A; int /*<<< orphan*/ * D; } ;
typedef  TYPE_1__ M68KRegs ;

/* Variables and functions */
 TYPE_3__* M68K ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ) ; 

void M68KSetRegisters(const M68KRegs *regs)
{
   int i;

   if (regs != NULL)
   {
      for (i = 0; i < 8; i++)
      {
         M68K->SetDReg(i, regs->D[i]);
         M68K->SetAReg(i, regs->A[i]);
      }
      M68K->SetSR(regs->SR);
      M68K->SetPC(regs->PC);
   }
}