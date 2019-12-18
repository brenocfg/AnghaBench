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
struct bdx_priv {int /*<<< orphan*/  ndev; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER ; 
 int /*<<< orphan*/  RET () ; 
 int /*<<< orphan*/  bdx_disable_interrupts (struct bdx_priv*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bdx_hw_stop(struct bdx_priv *priv)
{
	ENTER;
	bdx_disable_interrupts(priv);
	free_irq(priv->pdev->irq, priv->ndev);

	netif_carrier_off(priv->ndev);
	netif_stop_queue(priv->ndev);

	RET();
}