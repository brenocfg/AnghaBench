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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  ctl_pin_status_mask; } ;
struct cx231xx {TYPE_1__ board; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIN_CTRL ; 
 int vid_blk_read_word (struct cx231xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int vid_blk_write_word (struct cx231xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cx231xx_init_ctrl_pin_status(struct cx231xx *dev)
{
	u32 value;
	int status = 0;

	status = vid_blk_read_word(dev, PIN_CTRL, &value);
	value |= (~dev->board.ctl_pin_status_mask);
	status = vid_blk_write_word(dev, PIN_CTRL, value);

	return status;
}