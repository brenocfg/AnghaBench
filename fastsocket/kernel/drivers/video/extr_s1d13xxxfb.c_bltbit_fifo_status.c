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
typedef  int u8 ;
struct fb_info {int /*<<< orphan*/  par; } ;

/* Variables and functions */
 int BBLT_FIFO_EMPTY ; 
 int BBLT_FIFO_FULL ; 
 int BBLT_FIFO_NOT_FULL ; 
 int /*<<< orphan*/  S1DREG_BBLT_CTL0 ; 
 int s1d13xxxfb_readreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8
bltbit_fifo_status(struct fb_info *info)
{
	u8 status;

	status = s1d13xxxfb_readreg(info->par, S1DREG_BBLT_CTL0);

	/* its empty so room for 16 words */
	if (status & BBLT_FIFO_EMPTY)
		return 16;

	/* its full so we dont want to add */
	if (status & BBLT_FIFO_FULL)
		return 0;

	/* its atleast half full but we can add one atleast */
	if (status & BBLT_FIFO_NOT_FULL)
		return 1;

	return 0;
}