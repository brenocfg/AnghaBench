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
struct ipw2100_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipw2100_msg_initialize (struct ipw2100_priv*) ; 
 int /*<<< orphan*/  ipw2100_rx_initialize (struct ipw2100_priv*) ; 
 int /*<<< orphan*/  ipw2100_tx_initialize (struct ipw2100_priv*) ; 

__attribute__((used)) static void ipw2100_queues_initialize(struct ipw2100_priv *priv)
{
	ipw2100_tx_initialize(priv);
	ipw2100_rx_initialize(priv);
	ipw2100_msg_initialize(priv);
}