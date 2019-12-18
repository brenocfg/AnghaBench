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
struct netif {int /*<<< orphan*/  flags; scalar_t__ state; } ;
struct bba_priv {int dummy; } ;
typedef  scalar_t__ err_t ;

/* Variables and functions */
 scalar_t__ ERR_IF ; 
 scalar_t__ ERR_OK ; 
 int /*<<< orphan*/  EXI_CHANNEL_2 ; 
 int /*<<< orphan*/  EXI_RegisterEXICallback (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LWIP_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NETIF_DEBUG ; 
 int /*<<< orphan*/  NETIF_FLAG_LINK_UP ; 
 int /*<<< orphan*/  __bba_exi_stop (struct bba_priv*) ; 
 int /*<<< orphan*/  __bba_exi_wake (struct bba_priv*) ; 
 scalar_t__ __bba_get_linkstateasync (struct bba_priv*) ; 
 int /*<<< orphan*/ * bba_event_handler ; 
 scalar_t__ bba_probe (struct netif*) ; 

err_t bba_init(struct netif *dev)
{
	err_t ret;
	struct bba_priv *priv = (struct bba_priv*)dev->state;

	__bba_exi_stop(priv);

	LWIP_DEBUGF(NETIF_DEBUG, ("bba_init(call EXI_RegisterEXICallback())\n"));
	EXI_RegisterEXICallback(EXI_CHANNEL_2,bba_event_handler);

	ret = bba_probe(dev);
	if(ret!=ERR_OK) {
		EXI_RegisterEXICallback(EXI_CHANNEL_2,NULL);
		__bba_exi_wake(priv);
		return ret;
	}

	ret = __bba_get_linkstateasync(priv);
	if(ret) {
		dev->flags |= NETIF_FLAG_LINK_UP;
		ret = ERR_OK;
	} else {
		EXI_RegisterEXICallback(EXI_CHANNEL_2,NULL);
		ret = ERR_IF;
	}

	__bba_exi_wake(priv);
	return ret;
}