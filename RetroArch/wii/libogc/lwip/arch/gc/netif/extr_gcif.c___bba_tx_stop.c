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
struct bba_priv {scalar_t__ state; int /*<<< orphan*/  tq_xmit; } ;

/* Variables and functions */
 scalar_t__ ERR_TXPENDING ; 
 int /*<<< orphan*/  LWIP_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LWP_ThreadSleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NETIF_DEBUG ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ void __bba_tx_stop(struct bba_priv *priv)
{
	u32 level;

	_CPU_ISR_Disable(level);
	while(priv->state==ERR_TXPENDING) {
		LWIP_DEBUGF(NETIF_DEBUG,("__bba_tx_stop(pending tx)\n"));
		LWP_ThreadSleep(priv->tq_xmit);
	}
	priv->state = ERR_TXPENDING;
	_CPU_ISR_Restore(level);
}