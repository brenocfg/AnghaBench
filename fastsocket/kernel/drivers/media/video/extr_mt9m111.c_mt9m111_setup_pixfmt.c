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
typedef  int /*<<< orphan*/  u16 ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OUTPUT_FORMAT_CTRL2_A ; 
 int /*<<< orphan*/  OUTPUT_FORMAT_CTRL2_B ; 
 int reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt9m111_setup_pixfmt(struct i2c_client *client, u16 outfmt)
{
	int ret;

	ret = reg_write(OUTPUT_FORMAT_CTRL2_A, outfmt);
	if (!ret)
		ret = reg_write(OUTPUT_FORMAT_CTRL2_B, outfmt);
	return ret;
}