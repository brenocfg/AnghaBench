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
struct stmmac_priv {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stmmac_disable_irq (struct stmmac_priv*) ; 
 int /*<<< orphan*/  stmmac_has_work (struct stmmac_priv*) ; 

__attribute__((used)) static inline void _stmmac_schedule(struct stmmac_priv *priv)
{
	if (likely(stmmac_has_work(priv))) {
		stmmac_disable_irq(priv);
		napi_schedule(&priv->napi);
	}
}