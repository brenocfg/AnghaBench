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
struct hw {int dummy; } ;
struct TYPE_3__ {scalar_t__ srtctl; } ;
struct TYPE_4__ {TYPE_1__ bf; } ;
struct dai_ctrl_blk {TYPE_2__ dirty; int /*<<< orphan*/  srtctl; } ;

/* Variables and functions */
 scalar_t__ SRTICTL ; 
 scalar_t__ SRTSCTL ; 
 int /*<<< orphan*/  hw_write_20kx (struct hw*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dai_commit_write(struct hw *hw, unsigned int idx, void *blk)
{
	struct dai_ctrl_blk *ctl = blk;

	if (ctl->dirty.bf.srtctl) {
		if (idx < 4) {
			/* S/PDIF SRTs */
			hw_write_20kx(hw, SRTSCTL+0x4*idx, ctl->srtctl);
		} else {
			/* I2S SRT */
			hw_write_20kx(hw, SRTICTL, ctl->srtctl);
		}
		ctl->dirty.bf.srtctl = 0;
	}

	return 0;
}