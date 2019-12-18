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
struct TYPE_2__ {int coef; } ;
struct nvc0_pm_state {TYPE_1__ mem; } ;
struct nouveau_mem_exec_func {struct nvc0_pm_state* priv; int /*<<< orphan*/  dev; } ;
struct nouveau_device {int dummy; } ;

/* Variables and functions */
 struct nouveau_device* nouveau_dev (int /*<<< orphan*/ ) ; 
 int nv_rd32 (struct nouveau_device*,int) ; 
 int /*<<< orphan*/  nv_wait (struct nouveau_device*,int,int,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nouveau_device*,int,int) ; 

__attribute__((used)) static void
mclk_clock_set(struct nouveau_mem_exec_func *exec)
{
	struct nouveau_device *device = nouveau_dev(exec->dev);
	struct nvc0_pm_state *info = exec->priv;
	u32 ctrl = nv_rd32(device, 0x132000);

	nv_wr32(device, 0x137360, 0x00000001);
	nv_wr32(device, 0x137370, 0x00000000);
	nv_wr32(device, 0x137380, 0x00000000);
	if (ctrl & 0x00000001)
		nv_wr32(device, 0x132000, (ctrl &= ~0x00000001));

	nv_wr32(device, 0x132004, info->mem.coef);
	nv_wr32(device, 0x132000, (ctrl |= 0x00000001));
	nv_wait(device, 0x137390, 0x00000002, 0x00000002);
	nv_wr32(device, 0x132018, 0x00005000);

	nv_wr32(device, 0x137370, 0x00000001);
	nv_wr32(device, 0x137380, 0x00000001);
	nv_wr32(device, 0x137360, 0x00000000);
}