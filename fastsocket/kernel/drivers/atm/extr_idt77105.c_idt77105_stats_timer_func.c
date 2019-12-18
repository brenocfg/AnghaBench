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
struct idt77105_stats {int /*<<< orphan*/  rx_hec_errors; int /*<<< orphan*/  rx_cells; int /*<<< orphan*/  tx_cells; int /*<<< orphan*/  symbol_errors; } ;
struct idt77105_priv {struct idt77105_stats stats; struct atm_dev* dev; struct idt77105_priv* next; } ;
struct atm_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int /*<<< orphan*/  IDT77105_CTRSEL_RCC ; 
 int /*<<< orphan*/  IDT77105_CTRSEL_RHEC ; 
 int /*<<< orphan*/  IDT77105_CTRSEL_SEC ; 
 int /*<<< orphan*/  IDT77105_CTRSEL_TCC ; 
 scalar_t__ IDT77105_STATS_TIMER_PERIOD ; 
 scalar_t__ get_counter (struct atm_dev*,int /*<<< orphan*/ ) ; 
 struct idt77105_priv* idt77105_all ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  start_timer ; 
 int /*<<< orphan*/  stats_timer ; 

__attribute__((used)) static void idt77105_stats_timer_func(unsigned long dummy)
{
	struct idt77105_priv *walk;
	struct atm_dev *dev;
	struct idt77105_stats *stats;

        DPRINTK("IDT77105 gathering statistics\n");
	for (walk = idt77105_all; walk; walk = walk->next) {
		dev = walk->dev;
                
		stats = &walk->stats;
                stats->symbol_errors += get_counter(dev, IDT77105_CTRSEL_SEC);
                stats->tx_cells += get_counter(dev, IDT77105_CTRSEL_TCC);
                stats->rx_cells += get_counter(dev, IDT77105_CTRSEL_RCC);
                stats->rx_hec_errors += get_counter(dev, IDT77105_CTRSEL_RHEC);
	}
        if (!start_timer) mod_timer(&stats_timer,jiffies+IDT77105_STATS_TIMER_PERIOD);
}