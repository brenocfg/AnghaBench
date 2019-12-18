#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned long data; void (* function ) (unsigned long) ;scalar_t__ expires; } ;
struct scc_channel {TYPE_1__ tx_t; } ;

/* Variables and functions */
 unsigned long HZ ; 
 unsigned long TIMER_OFF ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  del_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 

__attribute__((used)) static void __scc_start_tx_timer(struct scc_channel *scc, void (*handler)(unsigned long), unsigned long when)
{
	del_timer(&scc->tx_t);

	if (when == 0)
	{
		handler((unsigned long) scc);
	} else 
	if (when != TIMER_OFF)
	{
		scc->tx_t.data = (unsigned long) scc;
		scc->tx_t.function = handler;
		scc->tx_t.expires = jiffies + (when*HZ)/100;
		add_timer(&scc->tx_t);
	}
}