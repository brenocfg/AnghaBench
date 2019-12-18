#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct btmrvl_private {TYPE_1__* adapter; } ;
struct TYPE_2__ {int /*<<< orphan*/  cmd_wait_q; int /*<<< orphan*/  ps_state; int /*<<< orphan*/  tx_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  PS_AWAKE ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void btmrvl_init_adapter(struct btmrvl_private *priv)
{
	skb_queue_head_init(&priv->adapter->tx_queue);

	priv->adapter->ps_state = PS_AWAKE;

	init_waitqueue_head(&priv->adapter->cmd_wait_q);
}