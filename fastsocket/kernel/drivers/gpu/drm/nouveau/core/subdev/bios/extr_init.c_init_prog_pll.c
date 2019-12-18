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
typedef  int /*<<< orphan*/  u32 ;
struct nvbios_init {int /*<<< orphan*/  bios; } ;
struct nouveau_clock {int (* pll_set ) (struct nouveau_clock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ init_exec (struct nvbios_init*) ; 
 struct nouveau_clock* nouveau_clock (int /*<<< orphan*/ ) ; 
 int stub1 (struct nouveau_clock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
init_prog_pll(struct nvbios_init *init, u32 id, u32 freq)
{
	struct nouveau_clock *clk = nouveau_clock(init->bios);
	if (clk && clk->pll_set && init_exec(init)) {
		int ret = clk->pll_set(clk, id, freq);
		if (ret)
			warn("failed to prog pll 0x%08x to %dkHz\n", id, freq);
	}
}