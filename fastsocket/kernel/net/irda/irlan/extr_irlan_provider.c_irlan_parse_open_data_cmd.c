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
struct sk_buff {int dummy; } ;
struct irlan_cb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_OPEN_DATA_CHANNEL ; 
 int /*<<< orphan*/  irlan_open_data_tsap (struct irlan_cb*) ; 
 int irlan_provider_parse_command (struct irlan_cb*,int /*<<< orphan*/ ,struct sk_buff*) ; 

int irlan_parse_open_data_cmd(struct irlan_cb *self, struct sk_buff *skb)
{
	int ret;

	ret = irlan_provider_parse_command(self, CMD_OPEN_DATA_CHANNEL, skb);

	/* Open data channel */
	irlan_open_data_tsap(self);

	return ret;
}