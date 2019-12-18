#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int /*<<< orphan*/ * proposed_mac; } ;
struct flexcop_device {scalar_t__ (* get_mac_addr ) (struct flexcop_device*,int /*<<< orphan*/ ) ;TYPE_1__ dvb_adapter; } ;
struct TYPE_4__ {scalar_t__ raw; } ;

/* Variables and functions */
 int /*<<< orphan*/  flexcop_determine_revision (struct flexcop_device*) ; 
 int /*<<< orphan*/  flexcop_device_exit (struct flexcop_device*) ; 
 int /*<<< orphan*/  flexcop_device_name (struct flexcop_device*,char*,char*) ; 
 int flexcop_dvb_init (struct flexcop_device*) ; 
 int flexcop_frontend_init (struct flexcop_device*) ; 
 int /*<<< orphan*/  flexcop_hw_filter_init (struct flexcop_device*) ; 
 int flexcop_i2c_init (struct flexcop_device*) ; 
 int /*<<< orphan*/  flexcop_mac_filter_ctrl (struct flexcop_device*,int) ; 
 int /*<<< orphan*/  flexcop_reset (struct flexcop_device*) ; 
 int /*<<< orphan*/  flexcop_set_mac_filter (struct flexcop_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flexcop_smc_ctrl (struct flexcop_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flexcop_sram_init (struct flexcop_device*) ; 
 TYPE_2__ ibi_zero ; 
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct flexcop_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 

int flexcop_device_initialize(struct flexcop_device *fc)
{
	int ret;
	ibi_zero.raw = 0;

	flexcop_reset(fc);
	flexcop_determine_revision(fc);
	flexcop_sram_init(fc);
	flexcop_hw_filter_init(fc);
	flexcop_smc_ctrl(fc, 0);

	if ((ret = flexcop_dvb_init(fc)))
		goto error;

	/* i2c has to be done before doing EEProm stuff -
	 * because the EEProm is accessed via i2c */
	ret = flexcop_i2c_init(fc);
	if (ret)
		goto error;

	/* do the MAC address reading after initializing the dvb_adapter */
	if (fc->get_mac_addr(fc, 0) == 0) {
		u8 *b = fc->dvb_adapter.proposed_mac;
		info("MAC address = %pM", b);
		flexcop_set_mac_filter(fc,b);
		flexcop_mac_filter_ctrl(fc,1);
	} else
		warn("reading of MAC address failed.\n");

	if ((ret = flexcop_frontend_init(fc)))
		goto error;

	flexcop_device_name(fc,"initialization of","complete");
	return 0;

error:
	flexcop_device_exit(fc);
	return ret;
}