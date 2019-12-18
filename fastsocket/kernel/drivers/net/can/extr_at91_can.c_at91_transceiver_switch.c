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
struct at91_priv {TYPE_1__* pdata; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* transceiver_switch ) (int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int) ; 

__attribute__((used)) static void at91_transceiver_switch(const struct at91_priv *priv, int on)
{
	if (priv->pdata && priv->pdata->transceiver_switch)
		priv->pdata->transceiver_switch(on);
}