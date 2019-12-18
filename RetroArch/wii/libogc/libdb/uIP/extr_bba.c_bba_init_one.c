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
struct uip_netif {scalar_t__ state; } ;
struct bba_priv {int revid; int devid; int acstart; } ;
typedef  int /*<<< orphan*/  s8_t ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  UIP_ERR_IF ; 
 int /*<<< orphan*/  __bba_init (struct uip_netif*) ; 

__attribute__((used)) static s8_t bba_init_one(struct uip_netif *dev)
{
	s32 ret;
	struct bba_priv *priv = (struct bba_priv*)dev->state;

	if(!priv) return UIP_ERR_IF;

	priv->revid = 0x00;
	priv->devid = 0xD107;
	priv->acstart = 0x4E;

	ret = __bba_init(dev);

	return ret;
}