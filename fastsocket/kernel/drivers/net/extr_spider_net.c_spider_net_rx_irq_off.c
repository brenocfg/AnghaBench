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
struct spider_net_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPIDER_NET_GHIINT0MSK ; 
 int SPIDER_NET_INT0_MASK_VALUE ; 
 int SPIDER_NET_RXINT ; 
 int /*<<< orphan*/  spider_net_write_reg (struct spider_net_card*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
spider_net_rx_irq_off(struct spider_net_card *card)
{
	u32 regvalue;

	regvalue = SPIDER_NET_INT0_MASK_VALUE & (~SPIDER_NET_RXINT);
	spider_net_write_reg(card, SPIDER_NET_GHIINT0MSK, regvalue);
}