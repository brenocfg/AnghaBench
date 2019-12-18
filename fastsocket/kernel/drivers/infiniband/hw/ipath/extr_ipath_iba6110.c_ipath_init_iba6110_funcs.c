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
struct ipath_devdata {int /*<<< orphan*/  ipath_f_ib_updown; int /*<<< orphan*/  ipath_f_config_jint; int /*<<< orphan*/  ipath_f_set_ib_cfg; int /*<<< orphan*/  ipath_f_get_ib_cfg; int /*<<< orphan*/  ipath_f_xgxs_reset; int /*<<< orphan*/  ipath_f_read_counters; int /*<<< orphan*/  ipath_f_config_ports; int /*<<< orphan*/  ipath_f_get_msgheader; int /*<<< orphan*/  ipath_f_intr_fallback; int /*<<< orphan*/  ipath_f_tidtemplate; int /*<<< orphan*/  ipath_f_free_irq; int /*<<< orphan*/  ipath_f_get_base_info; int /*<<< orphan*/  ipath_f_setextled; int /*<<< orphan*/  ipath_f_cleanup; int /*<<< orphan*/  ipath_f_put_tid; int /*<<< orphan*/  ipath_f_clear_tids; int /*<<< orphan*/  ipath_f_bringup_serdes; int /*<<< orphan*/  ipath_f_quiet_serdes; int /*<<< orphan*/  ipath_f_handle_hwerrors; int /*<<< orphan*/  ipath_f_early_init; int /*<<< orphan*/  ipath_f_init_hwerrors; int /*<<< orphan*/  ipath_f_get_boardname; int /*<<< orphan*/  ipath_f_reset; int /*<<< orphan*/  ipath_f_bus; int /*<<< orphan*/  ipath_f_intrsetup; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipath_ht_boardname ; 
 int /*<<< orphan*/  ipath_ht_bringup_serdes ; 
 int /*<<< orphan*/  ipath_ht_clear_tids ; 
 int /*<<< orphan*/  ipath_ht_config_jint ; 
 int /*<<< orphan*/  ipath_ht_config_ports ; 
 int /*<<< orphan*/  ipath_ht_early_init ; 
 int /*<<< orphan*/  ipath_ht_free_irq ; 
 int /*<<< orphan*/  ipath_ht_get_base_info ; 
 int /*<<< orphan*/  ipath_ht_get_ib_cfg ; 
 int /*<<< orphan*/  ipath_ht_get_msgheader ; 
 int /*<<< orphan*/  ipath_ht_handle_hwerrors ; 
 int /*<<< orphan*/  ipath_ht_ib_updown ; 
 int /*<<< orphan*/  ipath_ht_init_hwerrors ; 
 int /*<<< orphan*/  ipath_ht_intconfig ; 
 int /*<<< orphan*/  ipath_ht_nointr_fallback ; 
 int /*<<< orphan*/  ipath_ht_put_tid ; 
 int /*<<< orphan*/  ipath_ht_quiet_serdes ; 
 int /*<<< orphan*/  ipath_ht_read_counters ; 
 int /*<<< orphan*/  ipath_ht_set_ib_cfg ; 
 int /*<<< orphan*/  ipath_ht_tidtemplate ; 
 int /*<<< orphan*/  ipath_ht_xgxs_reset ; 
 int /*<<< orphan*/  ipath_init_ht_variables (struct ipath_devdata*) ; 
 int /*<<< orphan*/  ipath_setup_ht_cleanup ; 
 int /*<<< orphan*/  ipath_setup_ht_config ; 
 int /*<<< orphan*/  ipath_setup_ht_reset ; 
 int /*<<< orphan*/  ipath_setup_ht_setextled ; 

void ipath_init_iba6110_funcs(struct ipath_devdata *dd)
{
	dd->ipath_f_intrsetup = ipath_ht_intconfig;
	dd->ipath_f_bus = ipath_setup_ht_config;
	dd->ipath_f_reset = ipath_setup_ht_reset;
	dd->ipath_f_get_boardname = ipath_ht_boardname;
	dd->ipath_f_init_hwerrors = ipath_ht_init_hwerrors;
	dd->ipath_f_early_init = ipath_ht_early_init;
	dd->ipath_f_handle_hwerrors = ipath_ht_handle_hwerrors;
	dd->ipath_f_quiet_serdes = ipath_ht_quiet_serdes;
	dd->ipath_f_bringup_serdes = ipath_ht_bringup_serdes;
	dd->ipath_f_clear_tids = ipath_ht_clear_tids;
	dd->ipath_f_put_tid = ipath_ht_put_tid;
	dd->ipath_f_cleanup = ipath_setup_ht_cleanup;
	dd->ipath_f_setextled = ipath_setup_ht_setextled;
	dd->ipath_f_get_base_info = ipath_ht_get_base_info;
	dd->ipath_f_free_irq = ipath_ht_free_irq;
	dd->ipath_f_tidtemplate = ipath_ht_tidtemplate;
	dd->ipath_f_intr_fallback = ipath_ht_nointr_fallback;
	dd->ipath_f_get_msgheader = ipath_ht_get_msgheader;
	dd->ipath_f_config_ports = ipath_ht_config_ports;
	dd->ipath_f_read_counters = ipath_ht_read_counters;
	dd->ipath_f_xgxs_reset = ipath_ht_xgxs_reset;
	dd->ipath_f_get_ib_cfg = ipath_ht_get_ib_cfg;
	dd->ipath_f_set_ib_cfg = ipath_ht_set_ib_cfg;
	dd->ipath_f_config_jint = ipath_ht_config_jint;
	dd->ipath_f_ib_updown = ipath_ht_ib_updown;

	/*
	 * initialize chip-specific variables
	 */
	ipath_init_ht_variables(dd);
}