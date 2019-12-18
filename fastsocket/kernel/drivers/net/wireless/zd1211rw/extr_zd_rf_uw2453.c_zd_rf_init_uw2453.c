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
struct zd_rf {int /*<<< orphan*/ * priv; scalar_t__ update_channel_int; int /*<<< orphan*/  clear; int /*<<< orphan*/  patch_6m_band_edge; int /*<<< orphan*/  switch_radio_off; int /*<<< orphan*/  switch_radio_on; int /*<<< orphan*/  set_channel; int /*<<< orphan*/  init_hw; } ;
struct uw2453_priv {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uw2453_clear ; 
 int /*<<< orphan*/  uw2453_init_hw ; 
 int /*<<< orphan*/  uw2453_set_channel ; 
 int /*<<< orphan*/  uw2453_switch_radio_off ; 
 int /*<<< orphan*/  uw2453_switch_radio_on ; 
 int /*<<< orphan*/  zd_rf_generic_patch_6m ; 

int zd_rf_init_uw2453(struct zd_rf *rf)
{
	rf->init_hw = uw2453_init_hw;
	rf->set_channel = uw2453_set_channel;
	rf->switch_radio_on = uw2453_switch_radio_on;
	rf->switch_radio_off = uw2453_switch_radio_off;
	rf->patch_6m_band_edge = zd_rf_generic_patch_6m;
	rf->clear = uw2453_clear;
	/* we have our own TX integration code */
	rf->update_channel_int = 0;

	rf->priv = kmalloc(sizeof(struct uw2453_priv), GFP_KERNEL);
	if (rf->priv == NULL)
		return -ENOMEM;

	return 0;
}