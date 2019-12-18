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
struct zd_mac {int /*<<< orphan*/  chip; int /*<<< orphan*/  lock; scalar_t__ pass_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR_RX_FILTER ; 
 int /*<<< orphan*/  RX_FILTER_CTRL ; 
 int /*<<< orphan*/  STA_RX_FILTER ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int zd_iowrite32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_rx_filter(struct zd_mac *mac)
{
	unsigned long flags;
	u32 filter = STA_RX_FILTER;

	spin_lock_irqsave(&mac->lock, flags);
	if (mac->pass_ctrl)
		filter |= RX_FILTER_CTRL;
	spin_unlock_irqrestore(&mac->lock, flags);

	return zd_iowrite32(&mac->chip, CR_RX_FILTER, filter);
}