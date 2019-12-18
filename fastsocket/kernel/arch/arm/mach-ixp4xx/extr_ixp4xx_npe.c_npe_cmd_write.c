#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct npe {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  exec_status_cmd; int /*<<< orphan*/  exec_addr; int /*<<< orphan*/  exec_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void npe_cmd_write(struct npe *npe, u32 addr, int cmd, u32 data)
{
	__raw_writel(data, &npe->regs->exec_data);
	__raw_writel(addr, &npe->regs->exec_addr);
	__raw_writel(cmd, &npe->regs->exec_status_cmd);
}