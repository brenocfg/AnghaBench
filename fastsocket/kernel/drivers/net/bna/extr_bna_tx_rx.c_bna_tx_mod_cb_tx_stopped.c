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
struct bna_tx_mod {int /*<<< orphan*/  tx_stop_wc; } ;
struct bna_tx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_wc_down (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bna_tx_mod_cb_tx_stopped(void *arg, struct bna_tx *tx)
{
	struct bna_tx_mod *tx_mod = (struct bna_tx_mod *)arg;

	bfa_wc_down(&tx_mod->tx_stop_wc);
}