#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sh2regs_struct ;
struct TYPE_3__ {int /*<<< orphan*/  regs; } ;
typedef  TYPE_1__ SH2_struct ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

void SH2InterpreterSetRegisters(SH2_struct *context, const sh2regs_struct *regs)
{
   memcpy(&context->regs, regs, sizeof(sh2regs_struct));
}