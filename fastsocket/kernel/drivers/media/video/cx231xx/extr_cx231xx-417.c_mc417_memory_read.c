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
struct cx231xx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ITVC_READ_DIR ; 
 int /*<<< orphan*/  ITVC_WRITE_DIR ; 
 int MCI_MEMORY_ADDRESS_BYTE0 ; 
 int MCI_MEMORY_ADDRESS_BYTE1 ; 
 int MCI_MEMORY_ADDRESS_BYTE2 ; 
 int MCI_MEMORY_DATA_BYTE0 ; 
 int MCI_MEMORY_DATA_BYTE1 ; 
 int MCI_MEMORY_DATA_BYTE2 ; 
 int MCI_MEMORY_DATA_BYTE3 ; 
 int MCI_MODE_MEMORY_READ ; 
 int /*<<< orphan*/  getITVCReg (struct cx231xx*,int /*<<< orphan*/ ,int*) ; 
 int setITVCReg (struct cx231xx*,int /*<<< orphan*/ ,int) ; 
 int waitForMciComplete (struct cx231xx*) ; 

__attribute__((used)) static int mc417_memory_read(struct cx231xx *dev, u32 address, u32 *value)
{
	u32 temp = 0;
	u32 return_value = 0;
	int ret = 0;

	/*write address byte 2;*/
	temp = 0x82|MCI_MEMORY_ADDRESS_BYTE2 | MCI_MODE_MEMORY_READ |
		((address & 0x003F0000)>>8);
	temp = temp<<10;
	ret = setITVCReg(dev, ITVC_WRITE_DIR, temp);
	if (ret < 0)
		return ret;
	temp = temp|((0x05)<<10);
	setITVCReg(dev, ITVC_WRITE_DIR, temp);

	/*write address byte 1*/
	temp = 0x82|MCI_MEMORY_ADDRESS_BYTE1 | (address & 0xFF00);
	temp = temp<<10;
	setITVCReg(dev, ITVC_WRITE_DIR, temp);
	temp = temp|((0x05)<<10);
	setITVCReg(dev, ITVC_WRITE_DIR, temp);

	/*write address byte 0*/
	temp = 0x82|MCI_MEMORY_ADDRESS_BYTE0 | ((address & 0x00FF)<<8);
	temp = temp<<10;
	setITVCReg(dev, ITVC_WRITE_DIR, temp);
	temp = temp|((0x05)<<10);
	setITVCReg(dev, ITVC_WRITE_DIR, temp);

	/*Wait for MIRDY line*/
	ret = waitForMciComplete(dev);


	/*Read data byte 3;*/
	temp = (0x82|MCI_MEMORY_DATA_BYTE3)<<10;
	setITVCReg(dev, ITVC_READ_DIR, temp);
	temp = ((0x81|MCI_MEMORY_DATA_BYTE3)<<10);
	setITVCReg(dev, ITVC_READ_DIR, temp);
	getITVCReg(dev, ITVC_READ_DIR, &temp);
	return_value |= ((temp&0x03FC0000)<<6);
	setITVCReg(dev, ITVC_READ_DIR, (0x87<<10));

	/*Read data byte 2;*/
	temp = (0x82|MCI_MEMORY_DATA_BYTE2)<<10;
	setITVCReg(dev, ITVC_READ_DIR, temp);
	temp = ((0x81|MCI_MEMORY_DATA_BYTE2)<<10);
	setITVCReg(dev, ITVC_READ_DIR, temp);
	getITVCReg(dev, ITVC_READ_DIR, &temp);
	return_value |= ((temp&0x03FC0000)>>2);
	setITVCReg(dev, ITVC_READ_DIR, (0x87<<10));

	/* Read data byte 1;*/
	temp = (0x82|MCI_MEMORY_DATA_BYTE1)<<10;
	setITVCReg(dev, ITVC_READ_DIR, temp);
	temp = ((0x81|MCI_MEMORY_DATA_BYTE1)<<10);
	setITVCReg(dev, ITVC_READ_DIR, temp);
	getITVCReg(dev, ITVC_READ_DIR, &temp);
	return_value |= ((temp&0x03FC0000)>>10);
	setITVCReg(dev, ITVC_READ_DIR, (0x87<<10));

	/*Read data byte 0;*/
	temp = (0x82|MCI_MEMORY_DATA_BYTE0)<<10;
	setITVCReg(dev, ITVC_READ_DIR, temp);
	temp = ((0x81|MCI_MEMORY_DATA_BYTE0)<<10);
	setITVCReg(dev, ITVC_READ_DIR, temp);
	getITVCReg(dev, ITVC_READ_DIR, &temp);
	return_value |= ((temp&0x03FC0000)>>18);
	setITVCReg(dev, ITVC_READ_DIR, (0x87<<10));

	*value  = return_value;
	return ret;
}