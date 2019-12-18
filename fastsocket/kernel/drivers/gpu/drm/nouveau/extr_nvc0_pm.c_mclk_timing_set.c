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
struct nvc0_pm_state {struct nouveau_pm_level* perflvl; } ;
struct TYPE_2__ {int /*<<< orphan*/ * reg; } ;
struct nouveau_pm_level {TYPE_1__ timing; } ;
struct nouveau_mem_exec_func {struct nvc0_pm_state* priv; int /*<<< orphan*/  dev; } ;
struct nouveau_device {int dummy; } ;

/* Variables and functions */
 struct nouveau_device* nouveau_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_wr32 (struct nouveau_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mclk_timing_set(struct nouveau_mem_exec_func *exec)
{
	struct nouveau_device *device = nouveau_dev(exec->dev);
	struct nvc0_pm_state *info = exec->priv;
	struct nouveau_pm_level *perflvl = info->perflvl;
	int i;

	for (i = 0; i < 5; i++)
		nv_wr32(device, 0x10f290 + (i * 4), perflvl->timing.reg[i]);
}