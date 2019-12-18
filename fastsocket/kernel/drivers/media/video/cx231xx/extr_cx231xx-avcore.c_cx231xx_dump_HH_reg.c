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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct cx231xx {int dummy; } ;

/* Variables and functions */
 int AFE_CTRL_C2HH_SRC_CTRL ; 
 int /*<<< orphan*/  cx231xx_info (char*,int,...) ; 
 int /*<<< orphan*/  vid_blk_read_word (struct cx231xx*,int,int*) ; 
 int /*<<< orphan*/  vid_blk_write_word (struct cx231xx*,int,int) ; 

void cx231xx_dump_HH_reg(struct cx231xx *dev)
{
	u8 status = 0;
	u32 value = 0;
	u16  i = 0;

	value = 0x45005390;
	status = vid_blk_write_word(dev, 0x104, value);

	for (i = 0x100; i < 0x140; i++) {
		status = vid_blk_read_word(dev, i, &value);
		cx231xx_info("reg0x%x=0x%x\n", i, value);
		i = i+3;
	}

	for (i = 0x300; i < 0x400; i++) {
		status = vid_blk_read_word(dev, i, &value);
		cx231xx_info("reg0x%x=0x%x\n", i, value);
		i = i+3;
	}

	for (i = 0x400; i < 0x440; i++) {
		status = vid_blk_read_word(dev, i,  &value);
		cx231xx_info("reg0x%x=0x%x\n", i, value);
		i = i+3;
	}

	status = vid_blk_read_word(dev, AFE_CTRL_C2HH_SRC_CTRL, &value);
	cx231xx_info("AFE_CTRL_C2HH_SRC_CTRL=0x%x\n", value);
	vid_blk_write_word(dev, AFE_CTRL_C2HH_SRC_CTRL, 0x4485D390);
	status = vid_blk_read_word(dev, AFE_CTRL_C2HH_SRC_CTRL, &value);
	cx231xx_info("AFE_CTRL_C2HH_SRC_CTRL=0x%x\n", value);
}