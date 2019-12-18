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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct zd_rf {int dummy; } ;
struct zd_ioreq16 {int member_1; int /*<<< orphan*/  member_0; } ;
struct zd_chip {int dummy; } ;
struct TYPE_2__ {int config; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct zd_ioreq16 const*) ; 
 size_t CHAN_TO_PAIRIDX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UW2453_AUTOCAL_VCO_CFG ; 
 TYPE_1__* UW2453_PRIV (struct zd_rf*) ; 
#define  ZD_CR12 133 
 int /*<<< orphan*/  ZD_CR203 ; 
#define  ZD_CR77 132 
#define  ZD_CR78 131 
#define  ZD_CR79 130 
#define  ZD_CR80 129 
#define  ZD_CR81 128 
 int uw2453_init_mode (struct zd_chip*) ; 
 int uw2453_set_tx_gain_level (struct zd_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** uw2453_std_vco_cfg ; 
 int uw2453_synth_set_channel (struct zd_chip*,int /*<<< orphan*/ ,int) ; 
 int uw2453_write_vco_cfg (struct zd_chip*,int /*<<< orphan*/ ) ; 
 int zd_iowrite16_locked (struct zd_chip*,int,int /*<<< orphan*/ ) ; 
 int zd_iowrite16a_locked (struct zd_chip*,struct zd_ioreq16 const*,int /*<<< orphan*/ ) ; 
 struct zd_chip* zd_rf_to_chip (struct zd_rf*) ; 

__attribute__((used)) static int uw2453_set_channel(struct zd_rf *rf, u8 channel)
{
	int r;
	u16 vco_cfg;
	int config = UW2453_PRIV(rf)->config;
	bool autocal = (config == -1);
	struct zd_chip *chip = zd_rf_to_chip(rf);

	static const struct zd_ioreq16 ioreqs[] = {
		{ ZD_CR80,  0x30 }, { ZD_CR81,  0x30 }, { ZD_CR79,  0x58 },
		{ ZD_CR12,  0xf0 }, { ZD_CR77,  0x1b }, { ZD_CR78,  0x58 },
	};

	r = uw2453_synth_set_channel(chip, channel, autocal);
	if (r)
		return r;

	if (autocal)
		vco_cfg = UW2453_AUTOCAL_VCO_CFG;
	else
		vco_cfg = uw2453_std_vco_cfg[config][CHAN_TO_PAIRIDX(channel)];

	r = uw2453_write_vco_cfg(chip, vco_cfg);
	if (r)
		return r;

	r = uw2453_init_mode(chip);
	if (r)
		return r;

	r = zd_iowrite16a_locked(chip, ioreqs, ARRAY_SIZE(ioreqs));
	if (r)
		return r;

	r = uw2453_set_tx_gain_level(chip, channel);
	if (r)
		return r;

	return zd_iowrite16_locked(chip, 0x06, ZD_CR203);
}