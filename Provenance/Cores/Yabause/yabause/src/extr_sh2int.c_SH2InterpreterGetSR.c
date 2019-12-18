#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {int /*<<< orphan*/  all; } ;
struct TYPE_6__ {TYPE_1__ SR; } ;
struct TYPE_7__ {TYPE_2__ regs; } ;
typedef  TYPE_3__ SH2_struct ;

/* Variables and functions */

u32 SH2InterpreterGetSR(SH2_struct *context)
{
    return context->regs.SR.all;
}