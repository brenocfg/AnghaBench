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
struct netif {scalar_t__ state; } ;
struct bba_priv {int revid; int devid; int acstart; } ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_IF ; 
 int /*<<< orphan*/  ERR_OK ; 
 int /*<<< orphan*/  __bba_init (struct netif*) ; 

__attribute__((used)) static err_t bba_init_one(struct netif *dev)
{
	struct bba_priv *priv = (struct bba_priv*)dev->state;

	if(!priv) return ERR_IF;

	priv->revid = 0xf0;
	priv->devid = 0xD107;
	priv->acstart = 0x4E;

	__bba_init(dev);

	return ERR_OK;
}