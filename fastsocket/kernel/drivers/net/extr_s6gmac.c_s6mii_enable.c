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
 scalar_t__ S6_GMAC_MACCONF1 ; 
 int S6_GMAC_MACCONF1_SOFTRES ; 
 scalar_t__ S6_GMAC_MACMIICONF ; 
 int S6_GMAC_MACMIICONF_CSEL ; 
 int S6_GMAC_MACMIICONF_CSEL_DIV168 ; 
 int S6_GMAC_MACMIICONF_CSEL_MASK ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void s6mii_enable(struct s6gmac *pd)
{
	writel(readl(pd->reg + S6_GMAC_MACCONF1) &
		~(1 << S6_GMAC_MACCONF1_SOFTRES),
		pd->reg + S6_GMAC_MACCONF1);
	writel((readl(pd->reg + S6_GMAC_MACMIICONF)
		& ~(S6_GMAC_MACMIICONF_CSEL_MASK << S6_GMAC_MACMIICONF_CSEL))
		| (S6_GMAC_MACMIICONF_CSEL_DIV168 << S6_GMAC_MACMIICONF_CSEL),
		pd->reg + S6_GMAC_MACMIICONF);
}