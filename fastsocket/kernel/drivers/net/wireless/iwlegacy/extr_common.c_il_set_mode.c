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
struct il_priv {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_rxon_chain ) (struct il_priv*) ;} ;

/* Variables and functions */
 int il_commit_rxon (struct il_priv*) ; 
 int /*<<< orphan*/  il_connection_init_rx_config (struct il_priv*) ; 
 int /*<<< orphan*/  stub1 (struct il_priv*) ; 

__attribute__((used)) static int
il_set_mode(struct il_priv *il)
{
	il_connection_init_rx_config(il);

	if (il->ops->set_rxon_chain)
		il->ops->set_rxon_chain(il);

	return il_commit_rxon(il);
}