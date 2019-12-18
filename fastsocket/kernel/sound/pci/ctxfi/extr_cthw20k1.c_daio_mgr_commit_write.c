#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hw {int dummy; } ;
struct TYPE_5__ {int i2sictl; int i2soctl; int spoctl; int spictl; scalar_t__ daoimap; } ;
struct TYPE_6__ {TYPE_2__ bf; } ;
struct TYPE_4__ {int idx; int /*<<< orphan*/  aim; } ;
struct daio_mgr_ctrl_blk {TYPE_3__ dirty; TYPE_1__ daoimap; int /*<<< orphan*/  spictl; int /*<<< orphan*/  spoctl; int /*<<< orphan*/  i2sctl; } ;

/* Variables and functions */
 scalar_t__ DAOIMAP ; 
 scalar_t__ I2SCTL ; 
 scalar_t__ SPICTL ; 
 scalar_t__ SPOCTL ; 
 int /*<<< orphan*/  hw_write_20kx (struct hw*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int daio_mgr_commit_write(struct hw *hw, void *blk)
{
	struct daio_mgr_ctrl_blk *ctl = blk;
	int i;

	if (ctl->dirty.bf.i2sictl || ctl->dirty.bf.i2soctl) {
		for (i = 0; i < 4; i++) {
			if ((ctl->dirty.bf.i2sictl & (0x1 << i)))
				ctl->dirty.bf.i2sictl &= ~(0x1 << i);

			if ((ctl->dirty.bf.i2soctl & (0x1 << i)))
				ctl->dirty.bf.i2soctl &= ~(0x1 << i);
		}
		hw_write_20kx(hw, I2SCTL, ctl->i2sctl);
		mdelay(1);
	}
	if (ctl->dirty.bf.spoctl) {
		for (i = 0; i < 4; i++) {
			if ((ctl->dirty.bf.spoctl & (0x1 << i)))
				ctl->dirty.bf.spoctl &= ~(0x1 << i);
		}
		hw_write_20kx(hw, SPOCTL, ctl->spoctl);
		mdelay(1);
	}
	if (ctl->dirty.bf.spictl) {
		for (i = 0; i < 4; i++) {
			if ((ctl->dirty.bf.spictl & (0x1 << i)))
				ctl->dirty.bf.spictl &= ~(0x1 << i);
		}
		hw_write_20kx(hw, SPICTL, ctl->spictl);
		mdelay(1);
	}
	if (ctl->dirty.bf.daoimap) {
		hw_write_20kx(hw, DAOIMAP+ctl->daoimap.idx*4,
					ctl->daoimap.aim);
		ctl->dirty.bf.daoimap = 0;
	}

	return 0;
}