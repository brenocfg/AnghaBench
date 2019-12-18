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
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct brcms_c_info {int /*<<< orphan*/  hw; } ;
struct brcms_antselcfg {void** ant_config; } ;
struct TYPE_2__ {void** ant_config; } ;
struct antsel_info {TYPE_1__ antcfg_cur; struct brcms_c_info* wlc; } ;

/* Variables and functions */
 size_t ANT_SELCFG_RX_DEF ; 
 size_t ANT_SELCFG_TX_DEF ; 
 int /*<<< orphan*/  M_MIMO_ANTSEL_RXDFLT ; 
 int /*<<< orphan*/  M_MIMO_ANTSEL_TXDFLT ; 
 int /*<<< orphan*/  brcms_b_write_shm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_c_antsel_antcfg2antsel (struct antsel_info*,void*) ; 

__attribute__((used)) static int brcms_c_antsel_cfgupd(struct antsel_info *asi,
				 struct brcms_antselcfg *antsel)
{
	struct brcms_c_info *wlc = asi->wlc;
	u8 ant_cfg;
	u16 mimo_antsel;

	/* 1) Update TX antconfig for all frames that are not unicast data
	 *    (aka default TX)
	 */
	ant_cfg = antsel->ant_config[ANT_SELCFG_TX_DEF];
	mimo_antsel = brcms_c_antsel_antcfg2antsel(asi, ant_cfg);
	brcms_b_write_shm(wlc->hw, M_MIMO_ANTSEL_TXDFLT, mimo_antsel);
	/*
	 * Update driver stats for currently selected
	 * default tx/rx antenna config
	 */
	asi->antcfg_cur.ant_config[ANT_SELCFG_TX_DEF] = ant_cfg;

	/* 2) Update RX antconfig for all frames that are not unicast data
	 *    (aka default RX)
	 */
	ant_cfg = antsel->ant_config[ANT_SELCFG_RX_DEF];
	mimo_antsel = brcms_c_antsel_antcfg2antsel(asi, ant_cfg);
	brcms_b_write_shm(wlc->hw, M_MIMO_ANTSEL_RXDFLT, mimo_antsel);
	/*
	 * Update driver stats for currently selected
	 * default tx/rx antenna config
	 */
	asi->antcfg_cur.ant_config[ANT_SELCFG_RX_DEF] = ant_cfg;

	return 0;
}