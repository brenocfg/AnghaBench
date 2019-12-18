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
typedef  int v4l2_std_id ;
typedef  int u8 ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int ADV7180_STATUS1_AUTOD_MASK ; 
#define  ADV7180_STATUS1_AUTOD_NTSC_4_43 135 
#define  ADV7180_STATUS1_AUTOD_NTSM_M_J 134 
#define  ADV7180_STATUS1_AUTOD_PAL_60 133 
#define  ADV7180_STATUS1_AUTOD_PAL_B_G 132 
#define  ADV7180_STATUS1_AUTOD_PAL_COMB 131 
#define  ADV7180_STATUS1_AUTOD_PAL_M 130 
#define  ADV7180_STATUS1_AUTOD_SECAM 129 
#define  ADV7180_STATUS1_AUTOD_SECAM_525 128 
 int /*<<< orphan*/  ADV7180_STATUS1_REG ; 
 int V4L2_STD_NTSC_443 ; 
 int V4L2_STD_NTSC_M_JP ; 
 int V4L2_STD_PAL ; 
 int V4L2_STD_PAL_60 ; 
 int V4L2_STD_PAL_M ; 
 int V4L2_STD_PAL_N ; 
 int V4L2_STD_PAL_Nc ; 
 int V4L2_STD_SECAM ; 
 int V4L2_STD_UNKNOWN ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static v4l2_std_id determine_norm(struct i2c_client *client)
{
	u8 status1 = i2c_smbus_read_byte_data(client, ADV7180_STATUS1_REG);

	switch (status1 & ADV7180_STATUS1_AUTOD_MASK) {
	case ADV7180_STATUS1_AUTOD_NTSM_M_J:
		return V4L2_STD_NTSC_M_JP;
	case ADV7180_STATUS1_AUTOD_NTSC_4_43:
		return V4L2_STD_NTSC_443;
	case ADV7180_STATUS1_AUTOD_PAL_M:
		return V4L2_STD_PAL_M;
	case ADV7180_STATUS1_AUTOD_PAL_60:
		return V4L2_STD_PAL_60;
	case ADV7180_STATUS1_AUTOD_PAL_B_G:
		return V4L2_STD_PAL;
	case ADV7180_STATUS1_AUTOD_SECAM:
		return V4L2_STD_SECAM;
	case ADV7180_STATUS1_AUTOD_PAL_COMB:
		return V4L2_STD_PAL_Nc | V4L2_STD_PAL_N;
	case ADV7180_STATUS1_AUTOD_SECAM_525:
		return V4L2_STD_SECAM;
	default:
		return V4L2_STD_UNKNOWN;
	}
}