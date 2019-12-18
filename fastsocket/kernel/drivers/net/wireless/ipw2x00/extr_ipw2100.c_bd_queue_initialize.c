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
struct ipw2100_priv {int /*<<< orphan*/  net_dev; } ;
struct ipw2100_bd_queue {scalar_t__ next; scalar_t__ oldest; scalar_t__ entries; scalar_t__ nic; int /*<<< orphan*/  drv; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_DEBUG_INFO (char*,...) ; 
 int /*<<< orphan*/  write_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void bd_queue_initialize(struct ipw2100_priv *priv,
				struct ipw2100_bd_queue *q, u32 base, u32 size,
				u32 r, u32 w)
{
	IPW_DEBUG_INFO("enter\n");

	IPW_DEBUG_INFO("initializing bd queue at virt=%p, phys=%08x\n", q->drv,
		       (u32) q->nic);

	write_register(priv->net_dev, base, q->nic);
	write_register(priv->net_dev, size, q->entries);
	write_register(priv->net_dev, r, q->oldest);
	write_register(priv->net_dev, w, q->next);

	IPW_DEBUG_INFO("exit\n");
}