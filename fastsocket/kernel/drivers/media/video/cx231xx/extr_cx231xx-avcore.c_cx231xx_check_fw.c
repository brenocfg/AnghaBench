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
struct cx231xx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DL_CTL_ADDRESS_LOW ; 
 int vid_blk_read_byte (struct cx231xx*,int /*<<< orphan*/ ,int*) ; 

int cx231xx_check_fw(struct cx231xx *dev)
{
	u8 temp = 0;
	int status = 0;
	status = vid_blk_read_byte(dev, DL_CTL_ADDRESS_LOW, &temp);
	if (status < 0)
		return status;
	else
		return temp;

}