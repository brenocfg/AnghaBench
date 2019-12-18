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
typedef  int u32 ;
struct s6gmac {scalar_t__ reg; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ S6_GMAC_STATCARRY (int) ; 
 int S6_GMAC_STATCARRY1_RALN ; 
 int S6_GMAC_STATCARRY1_RBYT ; 
 int S6_GMAC_STATCARRY1_RCDE ; 
 int S6_GMAC_STATCARRY1_RDRP ; 
 int S6_GMAC_STATCARRY1_RFCS ; 
 int S6_GMAC_STATCARRY1_RFLR ; 
 int S6_GMAC_STATCARRY1_RFRG ; 
 int S6_GMAC_STATCARRY1_RJBR ; 
 int S6_GMAC_STATCARRY1_RMCA ; 
 int S6_GMAC_STATCARRY1_ROVR ; 
 int S6_GMAC_STATCARRY1_RPKT ; 
 int S6_GMAC_STATCARRY1_RUND ; 
 int S6_GMAC_STATCARRY2_TBYT ; 
 int S6_GMAC_STATCARRY2_TDRP ; 
 int S6_GMAC_STATCARRY2_TEDF ; 
 int S6_GMAC_STATCARRY2_TFCS ; 
 int S6_GMAC_STATCARRY2_TFRG ; 
 int S6_GMAC_STATCARRY2_TJBR ; 
 int S6_GMAC_STATCARRY2_TNCL ; 
 int S6_GMAC_STATCARRY2_TOVR ; 
 int S6_GMAC_STATCARRY2_TPKT ; 
 int S6_GMAC_STATCARRY2_TUND ; 
 int S6_GMAC_STATCARRY2_TXCL ; 
 scalar_t__ S6_GMAC_STATCARRYMSK (int) ; 
 struct s6gmac* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static inline void s6gmac_init_stats(struct net_device *dev)
{
	struct s6gmac *pd = netdev_priv(dev);
	u32 mask;
	mask =	1 << S6_GMAC_STATCARRY1_RDRP |
		1 << S6_GMAC_STATCARRY1_RJBR |
		1 << S6_GMAC_STATCARRY1_RFRG |
		1 << S6_GMAC_STATCARRY1_ROVR |
		1 << S6_GMAC_STATCARRY1_RUND |
		1 << S6_GMAC_STATCARRY1_RCDE |
		1 << S6_GMAC_STATCARRY1_RFLR |
		1 << S6_GMAC_STATCARRY1_RALN |
		1 << S6_GMAC_STATCARRY1_RMCA |
		1 << S6_GMAC_STATCARRY1_RFCS |
		1 << S6_GMAC_STATCARRY1_RPKT |
		1 << S6_GMAC_STATCARRY1_RBYT;
	writel(mask, pd->reg + S6_GMAC_STATCARRY(0));
	writel(~mask, pd->reg + S6_GMAC_STATCARRYMSK(0));
	mask =	1 << S6_GMAC_STATCARRY2_TDRP |
		1 << S6_GMAC_STATCARRY2_TNCL |
		1 << S6_GMAC_STATCARRY2_TXCL |
		1 << S6_GMAC_STATCARRY2_TEDF |
		1 << S6_GMAC_STATCARRY2_TPKT |
		1 << S6_GMAC_STATCARRY2_TBYT |
		1 << S6_GMAC_STATCARRY2_TFRG |
		1 << S6_GMAC_STATCARRY2_TUND |
		1 << S6_GMAC_STATCARRY2_TOVR |
		1 << S6_GMAC_STATCARRY2_TFCS |
		1 << S6_GMAC_STATCARRY2_TJBR;
	writel(mask, pd->reg + S6_GMAC_STATCARRY(1));
	writel(~mask, pd->reg + S6_GMAC_STATCARRYMSK(1));
}