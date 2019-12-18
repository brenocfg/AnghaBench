#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hwsq_ucode {int dummy; } ;
struct nv50_pm_state {struct hwsq_ucode mclk_hwsq; } ;
struct nouveau_mem_exec_func {struct nv50_pm_state* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  hwsq_wr32 (struct hwsq_ucode*,int,int) ; 

__attribute__((used)) static void
mclk_refresh_auto(struct nouveau_mem_exec_func *exec, bool enable)
{
	struct nv50_pm_state *info = exec->priv;
	struct hwsq_ucode *hwsq = &info->mclk_hwsq;

	hwsq_wr32(hwsq, 0x100210, enable ? 0x80000000 : 0x00000000);
}