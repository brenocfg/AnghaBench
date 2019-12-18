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
struct mt9m111 {scalar_t__ swap_yuv_y_chromas; scalar_t__ swap_yuv_cb_cr; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int MT9M111_OUTFMT_SWAP_YCbCr_C_Y ; 
 int MT9M111_OUTFMT_SWAP_YCbCr_Cb_Cr ; 
 int mt9m111_setup_pixfmt (struct i2c_client*,int) ; 
 struct mt9m111* to_mt9m111 (struct i2c_client*) ; 

__attribute__((used)) static int mt9m111_setfmt_yuv(struct i2c_client *client)
{
	struct mt9m111 *mt9m111 = to_mt9m111(client);
	int val = 0;

	if (mt9m111->swap_yuv_cb_cr)
		val |= MT9M111_OUTFMT_SWAP_YCbCr_Cb_Cr;
	if (mt9m111->swap_yuv_y_chromas)
		val |= MT9M111_OUTFMT_SWAP_YCbCr_C_Y;

	return mt9m111_setup_pixfmt(client, val);
}