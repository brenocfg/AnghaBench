#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* tail; } ;
struct spider_net_card {TYPE_2__ rx_chain; } ;
struct TYPE_3__ {int /*<<< orphan*/  bus_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPIDER_NET_GDADCHA ; 
 int /*<<< orphan*/  spider_net_write_reg (struct spider_net_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
spider_net_enable_rxchtails(struct spider_net_card *card)
{
	/* assume chain is aligned correctly */
	spider_net_write_reg(card, SPIDER_NET_GDADCHA ,
			     card->rx_chain.tail->bus_addr);
}