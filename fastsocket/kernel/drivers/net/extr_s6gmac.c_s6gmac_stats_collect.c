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
struct s6gmac_statinf {size_t net_index; int reg_off; scalar_t__ reg_size; } ;
struct s6gmac {scalar_t__ reg; int /*<<< orphan*/ * stats; } ;

/* Variables and functions */
 scalar_t__ S6_GMAC_STAT_REGS ; 
 int S6_STATS_B ; 
 scalar_t__ readl (scalar_t__) ; 

__attribute__((used)) static void s6gmac_stats_collect(struct s6gmac *pd,
		const struct s6gmac_statinf *inf)
{
	int b;
	for (b = 0; b < S6_STATS_B; b++) {
		if (inf[b].reg_size) {
			pd->stats[inf[b].net_index] +=
				readl(pd->reg + S6_GMAC_STAT_REGS
					+ sizeof(u32) * inf[b].reg_off);
		}
	}
}