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
typedef  scalar_t__ u32 ;
struct s6gmac {scalar_t__ reg; } ;

/* Variables and functions */
 scalar_t__ S6_GMAC_STATCARRY (int) ; 
 int /*<<< orphan*/  s6gmac_stats_carry (struct s6gmac*,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ s6gmac_stats_pending (struct s6gmac*,int) ; 
 int /*<<< orphan*/ ** statinf ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void s6gmac_stats_interrupt(struct s6gmac *pd, int carry)
{
	u32 mask;
	mask = s6gmac_stats_pending(pd, carry);
	if (mask) {
		writel(mask, pd->reg + S6_GMAC_STATCARRY(carry));
		s6gmac_stats_carry(pd, &statinf[carry][0], mask);
	}
}