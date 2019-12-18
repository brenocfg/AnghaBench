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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct dvb_usb_device {int dummy; } ;
typedef  int fe_bandwidth_t ;

/* Variables and functions */
#define  BANDWIDTH_6_MHZ 130 
#define  BANDWIDTH_7_MHZ 129 
#define  BANDWIDTH_8_MHZ 128 
 int EINVAL ; 
 int af9005_write_ofdm_register (struct dvb_usb_device*,int,scalar_t__) ; 
 int /*<<< orphan*/  err (char*,int) ; 

__attribute__((used)) static int af9005_fe_program_cfoe(struct dvb_usb_device *d, fe_bandwidth_t bw)
{
	u8 temp0, temp1, temp2, temp3, buf[4];
	int ret;
	u32 NS_coeff1_2048Nu;
	u32 NS_coeff1_8191Nu;
	u32 NS_coeff1_8192Nu;
	u32 NS_coeff1_8193Nu;
	u32 NS_coeff2_2k;
	u32 NS_coeff2_8k;

	switch (bw) {
	case BANDWIDTH_6_MHZ:
		NS_coeff1_2048Nu = 0x2ADB6DC;
		NS_coeff1_8191Nu = 0xAB7313;
		NS_coeff1_8192Nu = 0xAB6DB7;
		NS_coeff1_8193Nu = 0xAB685C;
		NS_coeff2_2k = 0x156DB6E;
		NS_coeff2_8k = 0x55B6DC;
		break;

	case BANDWIDTH_7_MHZ:
		NS_coeff1_2048Nu = 0x3200001;
		NS_coeff1_8191Nu = 0xC80640;
		NS_coeff1_8192Nu = 0xC80000;
		NS_coeff1_8193Nu = 0xC7F9C0;
		NS_coeff2_2k = 0x1900000;
		NS_coeff2_8k = 0x640000;
		break;

	case BANDWIDTH_8_MHZ:
		NS_coeff1_2048Nu = 0x3924926;
		NS_coeff1_8191Nu = 0xE4996E;
		NS_coeff1_8192Nu = 0xE49249;
		NS_coeff1_8193Nu = 0xE48B25;
		NS_coeff2_2k = 0x1C92493;
		NS_coeff2_8k = 0x724925;
		break;
	default:
		err("Invalid bandwith %d.", bw);
		return -EINVAL;
	}

	/*
	 *  write NS_coeff1_2048Nu
	 */

	temp0 = (u8) (NS_coeff1_2048Nu & 0x000000FF);
	temp1 = (u8) ((NS_coeff1_2048Nu & 0x0000FF00) >> 8);
	temp2 = (u8) ((NS_coeff1_2048Nu & 0x00FF0000) >> 16);
	temp3 = (u8) ((NS_coeff1_2048Nu & 0x03000000) >> 24);

	/*  big endian to make 8051 happy */
	buf[0] = temp3;
	buf[1] = temp2;
	buf[2] = temp1;
	buf[3] = temp0;

	/*  cfoe_NS_2k_coeff1_25_24 */
	ret = af9005_write_ofdm_register(d, 0xAE00, buf[0]);
	if (ret)
		return ret;

	/*  cfoe_NS_2k_coeff1_23_16 */
	ret = af9005_write_ofdm_register(d, 0xAE01, buf[1]);
	if (ret)
		return ret;

	/*  cfoe_NS_2k_coeff1_15_8 */
	ret = af9005_write_ofdm_register(d, 0xAE02, buf[2]);
	if (ret)
		return ret;

	/*  cfoe_NS_2k_coeff1_7_0 */
	ret = af9005_write_ofdm_register(d, 0xAE03, buf[3]);
	if (ret)
		return ret;

	/*
	 *  write NS_coeff2_2k
	 */

	temp0 = (u8) ((NS_coeff2_2k & 0x0000003F));
	temp1 = (u8) ((NS_coeff2_2k & 0x00003FC0) >> 6);
	temp2 = (u8) ((NS_coeff2_2k & 0x003FC000) >> 14);
	temp3 = (u8) ((NS_coeff2_2k & 0x01C00000) >> 22);

	/*  big endian to make 8051 happy */
	buf[0] = temp3;
	buf[1] = temp2;
	buf[2] = temp1;
	buf[3] = temp0;

	ret = af9005_write_ofdm_register(d, 0xAE04, buf[0]);
	if (ret)
		return ret;

	ret = af9005_write_ofdm_register(d, 0xAE05, buf[1]);
	if (ret)
		return ret;

	ret = af9005_write_ofdm_register(d, 0xAE06, buf[2]);
	if (ret)
		return ret;

	ret = af9005_write_ofdm_register(d, 0xAE07, buf[3]);
	if (ret)
		return ret;

	/*
	 *  write NS_coeff1_8191Nu
	 */

	temp0 = (u8) ((NS_coeff1_8191Nu & 0x000000FF));
	temp1 = (u8) ((NS_coeff1_8191Nu & 0x0000FF00) >> 8);
	temp2 = (u8) ((NS_coeff1_8191Nu & 0x00FFC000) >> 16);
	temp3 = (u8) ((NS_coeff1_8191Nu & 0x03000000) >> 24);

	/*  big endian to make 8051 happy */
	buf[0] = temp3;
	buf[1] = temp2;
	buf[2] = temp1;
	buf[3] = temp0;

	ret = af9005_write_ofdm_register(d, 0xAE08, buf[0]);
	if (ret)
		return ret;

	ret = af9005_write_ofdm_register(d, 0xAE09, buf[1]);
	if (ret)
		return ret;

	ret = af9005_write_ofdm_register(d, 0xAE0A, buf[2]);
	if (ret)
		return ret;

	ret = af9005_write_ofdm_register(d, 0xAE0B, buf[3]);
	if (ret)
		return ret;

	/*
	 *  write NS_coeff1_8192Nu
	 */

	temp0 = (u8) (NS_coeff1_8192Nu & 0x000000FF);
	temp1 = (u8) ((NS_coeff1_8192Nu & 0x0000FF00) >> 8);
	temp2 = (u8) ((NS_coeff1_8192Nu & 0x00FFC000) >> 16);
	temp3 = (u8) ((NS_coeff1_8192Nu & 0x03000000) >> 24);

	/*  big endian to make 8051 happy */
	buf[0] = temp3;
	buf[1] = temp2;
	buf[2] = temp1;
	buf[3] = temp0;

	ret = af9005_write_ofdm_register(d, 0xAE0C, buf[0]);
	if (ret)
		return ret;

	ret = af9005_write_ofdm_register(d, 0xAE0D, buf[1]);
	if (ret)
		return ret;

	ret = af9005_write_ofdm_register(d, 0xAE0E, buf[2]);
	if (ret)
		return ret;

	ret = af9005_write_ofdm_register(d, 0xAE0F, buf[3]);
	if (ret)
		return ret;

	/*
	 *  write NS_coeff1_8193Nu
	 */

	temp0 = (u8) ((NS_coeff1_8193Nu & 0x000000FF));
	temp1 = (u8) ((NS_coeff1_8193Nu & 0x0000FF00) >> 8);
	temp2 = (u8) ((NS_coeff1_8193Nu & 0x00FFC000) >> 16);
	temp3 = (u8) ((NS_coeff1_8193Nu & 0x03000000) >> 24);

	/*  big endian to make 8051 happy */
	buf[0] = temp3;
	buf[1] = temp2;
	buf[2] = temp1;
	buf[3] = temp0;

	ret = af9005_write_ofdm_register(d, 0xAE10, buf[0]);
	if (ret)
		return ret;

	ret = af9005_write_ofdm_register(d, 0xAE11, buf[1]);
	if (ret)
		return ret;

	ret = af9005_write_ofdm_register(d, 0xAE12, buf[2]);
	if (ret)
		return ret;

	ret = af9005_write_ofdm_register(d, 0xAE13, buf[3]);
	if (ret)
		return ret;

	/*
	 *  write NS_coeff2_8k
	 */

	temp0 = (u8) ((NS_coeff2_8k & 0x0000003F));
	temp1 = (u8) ((NS_coeff2_8k & 0x00003FC0) >> 6);
	temp2 = (u8) ((NS_coeff2_8k & 0x003FC000) >> 14);
	temp3 = (u8) ((NS_coeff2_8k & 0x01C00000) >> 22);

	/*  big endian to make 8051 happy */
	buf[0] = temp3;
	buf[1] = temp2;
	buf[2] = temp1;
	buf[3] = temp0;

	ret = af9005_write_ofdm_register(d, 0xAE14, buf[0]);
	if (ret)
		return ret;

	ret = af9005_write_ofdm_register(d, 0xAE15, buf[1]);
	if (ret)
		return ret;

	ret = af9005_write_ofdm_register(d, 0xAE16, buf[2]);
	if (ret)
		return ret;

	ret = af9005_write_ofdm_register(d, 0xAE17, buf[3]);
	return ret;

}