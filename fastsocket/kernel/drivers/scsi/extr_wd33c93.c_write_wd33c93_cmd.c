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
struct TYPE_3__ {int /*<<< orphan*/ * SCMD; int /*<<< orphan*/ * SASR; } ;
typedef  TYPE_1__ wd33c93_regs ;
typedef  int /*<<< orphan*/  uchar ;

/* Variables and functions */
 int /*<<< orphan*/  WD_COMMAND ; 
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static inline void
write_wd33c93_cmd(const wd33c93_regs regs, uchar cmd)
{
	*regs.SASR = WD_COMMAND;
	mb();
	*regs.SCMD = cmd;
	mb();
}