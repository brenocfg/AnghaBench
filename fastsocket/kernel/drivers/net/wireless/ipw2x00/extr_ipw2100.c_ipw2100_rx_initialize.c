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
struct TYPE_3__ {int /*<<< orphan*/  nic; } ;
struct TYPE_4__ {scalar_t__ available; scalar_t__ entries; scalar_t__ next; scalar_t__ oldest; } ;
struct ipw2100_priv {TYPE_1__ status_queue; int /*<<< orphan*/  net_dev; TYPE_2__ rx_queue; int /*<<< orphan*/  rxq_stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_STAT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPW_DEBUG_INFO (char*) ; 
 int /*<<< orphan*/  IPW_MEM_HOST_SHARED_RX_BD_BASE ; 
 int /*<<< orphan*/  IPW_MEM_HOST_SHARED_RX_BD_SIZE ; 
 int /*<<< orphan*/  IPW_MEM_HOST_SHARED_RX_READ_INDEX ; 
 int /*<<< orphan*/  IPW_MEM_HOST_SHARED_RX_STATUS_BASE ; 
 int /*<<< orphan*/  IPW_MEM_HOST_SHARED_RX_WRITE_INDEX ; 
 int /*<<< orphan*/  SET_STAT (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  bd_queue_initialize (struct ipw2100_priv*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipw2100_rx_initialize(struct ipw2100_priv *priv)
{
	IPW_DEBUG_INFO("enter\n");

	priv->rx_queue.oldest = 0;
	priv->rx_queue.available = priv->rx_queue.entries - 1;
	priv->rx_queue.next = priv->rx_queue.entries - 1;

	INIT_STAT(&priv->rxq_stat);
	SET_STAT(&priv->rxq_stat, priv->rx_queue.available);

	bd_queue_initialize(priv, &priv->rx_queue,
			    IPW_MEM_HOST_SHARED_RX_BD_BASE,
			    IPW_MEM_HOST_SHARED_RX_BD_SIZE,
			    IPW_MEM_HOST_SHARED_RX_READ_INDEX,
			    IPW_MEM_HOST_SHARED_RX_WRITE_INDEX);

	/* set up the status queue */
	write_register(priv->net_dev, IPW_MEM_HOST_SHARED_RX_STATUS_BASE,
		       priv->status_queue.nic);

	IPW_DEBUG_INFO("exit\n");
}