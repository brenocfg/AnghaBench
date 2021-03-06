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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  MACL; } ;
struct TYPE_5__ {TYPE_1__ regs; } ;
typedef  TYPE_2__ SH2_struct ;

/* Variables and functions */

void SH2InterpreterSetMACL(SH2_struct *context, u32 value)
{
    context->regs.MACL = value;
}