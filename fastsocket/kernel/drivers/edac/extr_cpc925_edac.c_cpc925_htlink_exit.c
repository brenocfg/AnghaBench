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
struct cpc925_dev_info {scalar_t__ vbase; } ;

/* Variables and functions */
 int /*<<< orphan*/  HT_ERRCTRL_ENABLE ; 
 scalar_t__ REG_ERRCTRL_OFFSET ; 
 int /*<<< orphan*/  __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void cpc925_htlink_exit(struct cpc925_dev_info *dev_info)
{
	u32 ht_errctrl;

	ht_errctrl = __raw_readl(dev_info->vbase + REG_ERRCTRL_OFFSET);
	ht_errctrl &= ~HT_ERRCTRL_ENABLE;
	__raw_writel(ht_errctrl, dev_info->vbase + REG_ERRCTRL_OFFSET);
}