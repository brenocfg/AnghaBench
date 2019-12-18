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
 scalar_t__ ERR_OK ; 
 scalar_t__ ERR_TXPENDING ; 
 int /*<<< orphan*/  LWP_ThreadBroadcast (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ void __bba_tx_wake(struct bba_priv *priv)
{
	u32 level;

	_CPU_ISR_Disable(level);
	if(priv->state==ERR_TXPENDING) {
		priv->state = ERR_OK;
		LWP_ThreadBroadcast(priv->tq_xmit);
	}
	_CPU_ISR_Restore(level);
}