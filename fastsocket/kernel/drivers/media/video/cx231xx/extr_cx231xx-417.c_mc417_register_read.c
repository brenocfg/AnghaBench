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
typedef  int u32 ;
typedef  int u16 ;
struct cx231xx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ITVC_READ_DIR ; 
 int /*<<< orphan*/  ITVC_WRITE_DIR ; 
 int MCI_MODE_REGISTER_READ ; 
 int MCI_REGISTER_ADDRESS_BYTE0 ; 
 int MCI_REGISTER_ADDRESS_BYTE1 ; 
 int MCI_REGISTER_DATA_BYTE0 ; 
 int MCI_REGISTER_DATA_BYTE1 ; 
 int MCI_REGISTER_DATA_BYTE2 ; 
 int MCI_REGISTER_DATA_BYTE3 ; 
 int MCI_REGISTER_MODE ; 
 int /*<<< orphan*/  getITVCReg (struct cx231xx*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  setITVCReg (struct cx231xx*,int /*<<< orphan*/ ,int) ; 
 int waitForMciComplete (struct cx231xx*) ; 

__attribute__((used)) static int mc417_register_read(struct cx231xx *dev, u16 address, u32 *value)
{
	/*write address byte 0;*/
	u32 temp;
	u32 return_value = 0;
	int ret = 0;

	temp = 0x82 | MCI_REGISTER_ADDRESS_BYTE0 | ((address & 0x00FF) << 8);
	temp = temp << 10;
	setITVCReg(dev, ITVC_WRITE_DIR, temp);
	temp = temp | ((0x05) << 10);
	setITVCReg(dev, ITVC_WRITE_DIR, temp);

	/*write address byte 1;*/
	temp = 0x82 | MCI_REGISTER_ADDRESS_BYTE1 | (address & 0xFF00);
	temp = temp << 10;
	setITVCReg(dev, ITVC_WRITE_DIR, temp);
	temp = temp | ((0x05) << 10);
	setITVCReg(dev, ITVC_WRITE_DIR, temp);

	/*write that the mode is read;*/
	temp = 0x82 | MCI_REGISTER_MODE | MCI_MODE_REGISTER_READ;
	temp = temp << 10;
	setITVCReg(dev, ITVC_WRITE_DIR, temp);
	temp = temp | ((0x05) << 10);
	setITVCReg(dev, ITVC_WRITE_DIR, temp);

	/*wait for the MIRDY line to be asserted ,
	signalling that the read is done;*/
	ret = waitForMciComplete(dev);

	/*switch the DATA- GPIO to input mode;*/

	/*Read data byte 0;*/
	temp = (0x82 | MCI_REGISTER_DATA_BYTE0) << 10;
	setITVCReg(dev, ITVC_READ_DIR, temp);
	temp = ((0x81 | MCI_REGISTER_DATA_BYTE0) << 10);
	setITVCReg(dev, ITVC_READ_DIR, temp);
	getITVCReg(dev, ITVC_READ_DIR, &temp);
	return_value |= ((temp & 0x03FC0000) >> 18);
	setITVCReg(dev, ITVC_READ_DIR, (0x87 << 10));

	/* Read data byte 1;*/
	temp = (0x82 | MCI_REGISTER_DATA_BYTE1) << 10;
	setITVCReg(dev, ITVC_READ_DIR, temp);
	temp = ((0x81 | MCI_REGISTER_DATA_BYTE1) << 10);
	setITVCReg(dev, ITVC_READ_DIR, temp);
	getITVCReg(dev, ITVC_READ_DIR, &temp);

	return_value |= ((temp & 0x03FC0000) >> 10);
	setITVCReg(dev, ITVC_READ_DIR, (0x87 << 10));

	/*Read data byte 2;*/
	temp = (0x82 | MCI_REGISTER_DATA_BYTE2) << 10;
	setITVCReg(dev, ITVC_READ_DIR, temp);
	temp = ((0x81 | MCI_REGISTER_DATA_BYTE2) << 10);
	setITVCReg(dev, ITVC_READ_DIR, temp);
	getITVCReg(dev, ITVC_READ_DIR, &temp);
	return_value |= ((temp & 0x03FC0000) >> 2);
	setITVCReg(dev, ITVC_READ_DIR, (0x87 << 10));

	/*Read data byte 3;*/
	temp = (0x82 | MCI_REGISTER_DATA_BYTE3) << 10;
	setITVCReg(dev, ITVC_READ_DIR, temp);
	temp = ((0x81 | MCI_REGISTER_DATA_BYTE3) << 10);
	setITVCReg(dev, ITVC_READ_DIR, temp);
	getITVCReg(dev, ITVC_READ_DIR, &temp);
	return_value |= ((temp & 0x03FC0000) << 6);
	setITVCReg(dev, ITVC_READ_DIR, (0x87 << 10));

	*value  = return_value;


	return ret;
}