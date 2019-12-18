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
struct s6gmac {scalar_t__ reg; } ;

/* Variables and functions */
 int ETIME ; 
 scalar_t__ S6_GMAC_MACMIIINDI ; 
 scalar_t__ readl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int s6mii_busy(struct s6gmac *pd, int tmo)
{
	while (readl(pd->reg + S6_GMAC_MACMIIINDI)) {
		if (--tmo == 0)
			return -ETIME;
		udelay(64);
	}
	return 0;
}