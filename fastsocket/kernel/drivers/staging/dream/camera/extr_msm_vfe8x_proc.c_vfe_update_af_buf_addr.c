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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ boolean ;
struct TYPE_2__ {scalar_t__ vfebase; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ VFE_BUS_STATS_AF_WR_PING_ADDR ; 
 scalar_t__ VFE_BUS_STATS_AF_WR_PONG_ADDR ; 
 TYPE_1__* ctrl ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
vfe_update_af_buf_addr(boolean pipo, uint32_t addr)
{
	if (pipo == FALSE)
		writel(addr, ctrl->vfebase + VFE_BUS_STATS_AF_WR_PING_ADDR);
	else
		writel(addr, ctrl->vfebase + VFE_BUS_STATS_AF_WR_PONG_ADDR);
}