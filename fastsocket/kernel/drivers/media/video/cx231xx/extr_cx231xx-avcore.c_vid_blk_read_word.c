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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct cx231xx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VID_BLK_I2C_ADDRESS ; 
 int cx231xx_read_i2c_data (struct cx231xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int vid_blk_read_word(struct cx231xx *dev, u16 saddr, u32 *data)
{
	return cx231xx_read_i2c_data(dev, VID_BLK_I2C_ADDRESS,
					saddr, 2, data, 4);
}