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
struct at91_priv {int tx_next; } ;

/* Variables and functions */
 int AT91_NEXT_PRIO_SHIFT ; 

__attribute__((used)) static inline int get_tx_next_prio(const struct at91_priv *priv)
{
	return (priv->tx_next >> AT91_NEXT_PRIO_SHIFT) & 0xf;
}