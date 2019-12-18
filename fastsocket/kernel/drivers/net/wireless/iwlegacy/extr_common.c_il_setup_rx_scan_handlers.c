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
 size_t C_SCAN ; 
 size_t N_SCAN_COMPLETE ; 
 size_t N_SCAN_RESULTS ; 
 size_t N_SCAN_START ; 
 int /*<<< orphan*/  il_hdl_scan ; 
 int /*<<< orphan*/  il_hdl_scan_complete ; 
 int /*<<< orphan*/  il_hdl_scan_results ; 
 int /*<<< orphan*/  il_hdl_scan_start ; 

void
il_setup_rx_scan_handlers(struct il_priv *il)
{
	/* scan handlers */
	il->handlers[C_SCAN] = il_hdl_scan;
	il->handlers[N_SCAN_START] = il_hdl_scan_start;
	il->handlers[N_SCAN_RESULTS] = il_hdl_scan_results;
	il->handlers[N_SCAN_COMPLETE] = il_hdl_scan_complete;
}