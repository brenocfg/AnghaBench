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
typedef  size_t u32 ;
struct emac_rxch {int teardown_pending; } ;
struct emac_priv {struct emac_rxch** rxch; } ;

/* Variables and functions */
 size_t BIT (size_t) ; 
 int /*<<< orphan*/  EMAC_RXINTMASKCLEAR ; 
 int /*<<< orphan*/  EMAC_RXTEARDOWN ; 
 int /*<<< orphan*/  emac_rxch_teardown (struct emac_priv*,size_t) ; 
 int /*<<< orphan*/  emac_write (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void emac_stop_rxch(struct emac_priv *priv, u32 ch)
{
	struct emac_rxch *rxch = priv->rxch[ch];

	if (rxch) {
		rxch->teardown_pending = 1;
		emac_write(EMAC_RXTEARDOWN, ch);
		/* wait for teardown complete */
		emac_rxch_teardown(priv, ch);
		rxch->teardown_pending = 0;
		emac_write(EMAC_RXINTMASKCLEAR, BIT(ch));
	}
}