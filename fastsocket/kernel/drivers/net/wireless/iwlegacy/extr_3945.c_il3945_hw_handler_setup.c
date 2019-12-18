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
struct il_priv {int /*<<< orphan*/ * handlers; } ;

/* Variables and functions */
 size_t C_TX ; 
 size_t N_3945_RX ; 
 int /*<<< orphan*/  il3945_hdl_rx ; 
 int /*<<< orphan*/  il3945_hdl_tx ; 

void
il3945_hw_handler_setup(struct il_priv *il)
{
	il->handlers[C_TX] = il3945_hdl_tx;
	il->handlers[N_3945_RX] = il3945_hdl_rx;
}