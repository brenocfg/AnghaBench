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
typedef  int u16 ;
struct usb_device {int dummy; } ;
struct firmware {int size; scalar_t__ data; } ;

/* Variables and functions */
 int ENODEV ; 
 int check_sum (int*,int) ; 
 int /*<<< orphan*/  deb_info (int,char*,int,int,int) ; 
 int /*<<< orphan*/  info (char*,...) ; 
 int lme2510_bulk_read (struct usb_device*,int*,int,int) ; 
 int lme2510_bulk_write (struct usb_device*,int*,int,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int,int,int,int,int*,int,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lme2510_download_firmware(struct usb_device *dev,
					const struct firmware *fw)
{
	int ret = 0;
	u8 data[512] = {0};
	u16 j, wlen, len_in, start, end;
	u8 packet_size, dlen, i;
	u8 *fw_data;

	packet_size = 0x31;
	len_in = 1;


	info("FRM Starting Firmware Download");

	for (i = 1; i < 3; i++) {
		start = (i == 1) ? 0 : 512;
		end = (i == 1) ? 512 : fw->size;
		for (j = start; j < end; j += (packet_size+1)) {
			fw_data = (u8 *)(fw->data + j);
			if ((end - j) > packet_size) {
				data[0] = i;
				dlen = packet_size;
			} else {
				data[0] = i | 0x80;
				dlen = (u8)(end - j)-1;
			}
		data[1] = dlen;
		memcpy(&data[2], fw_data, dlen+1);
		wlen = (u8) dlen + 4;
		data[wlen-1] = check_sum(fw_data, dlen+1);
		deb_info(1, "Data S=%02x:E=%02x CS= %02x", data[3],
				data[dlen+2], data[dlen+3]);
		ret |= lme2510_bulk_write(dev, data,  wlen, 1);
		ret |= lme2510_bulk_read(dev, data, len_in , 1);
		ret |= (data[0] == 0x88) ? 0 : -1;
		}
	}

	usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
			0x06, 0x80, 0x0200, 0x00, data, 0x0109, 1000);


	data[0] = 0x8a;
	len_in = 1;
	msleep(2000);
	ret |= lme2510_bulk_write(dev, data , len_in, 1); /*Resetting*/
	ret |= lme2510_bulk_read(dev, data, len_in, 1);
	msleep(400);

	if (ret < 0)
		info("FRM Firmware Download Failed (%04x)" , ret);
	else
		info("FRM Firmware Download Completed - Resetting Device");


	return (ret < 0) ? -ENODEV : 0;
}