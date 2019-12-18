#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct usb_device {int dummy; } ;
struct hexline {int addr; int len; int chk; int type; int /*<<< orphan*/  data; } ;
struct firmware {int dummy; } ;
typedef  int /*<<< orphan*/  b ;
struct TYPE_10__ {int num_adapters; TYPE_4__* adapter; } ;
struct TYPE_6__ {int buffersize; } ;
struct TYPE_7__ {TYPE_1__ bulk; } ;
struct TYPE_8__ {TYPE_2__ u; } ;
struct TYPE_9__ {TYPE_3__ stream; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  REQUEST_GET_VERSION ; 
 int /*<<< orphan*/  USB_CTRL_GET_TIMEOUT ; 
 int USB_DIR_IN ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  deb_fwdata (char*,int,int,int) ; 
 int dib0700_device_count ; 
 TYPE_5__* dib0700_devices ; 
 int dib0700_jumpram (struct usb_device*,int) ; 
 int dvb_usb_get_hexline (struct firmware const*,struct hexline*,int*) ; 
 int /*<<< orphan*/  err (char*,int,int) ; 
 int /*<<< orphan*/  info (char*) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int nb_packet_buffer_size ; 
 int usb_bulk_msg (struct usb_device*,int /*<<< orphan*/ ,int*,int,int*,int) ; 
 int /*<<< orphan*/  usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (struct usb_device*,int) ; 

int dib0700_download_firmware(struct usb_device *udev, const struct firmware *fw)
{
	struct hexline hx;
	int pos = 0, ret, act_len, i, adap_num;
	u8 b[16];
	u32 fw_version;

	u8 buf[260];

	while ((ret = dvb_usb_get_hexline(fw, &hx, &pos)) > 0) {
		deb_fwdata("writing to address 0x%08x (buffer: 0x%02x %02x)\n",
				hx.addr, hx.len, hx.chk);

		buf[0] = hx.len;
		buf[1] = (hx.addr >> 8) & 0xff;
		buf[2] =  hx.addr       & 0xff;
		buf[3] = hx.type;
		memcpy(&buf[4],hx.data,hx.len);
		buf[4+hx.len] = hx.chk;

		ret = usb_bulk_msg(udev,
			usb_sndbulkpipe(udev, 0x01),
			buf,
			hx.len + 5,
			&act_len,
			1000);

		if (ret < 0) {
			err("firmware download failed at %d with %d",pos,ret);
			return ret;
		}
	}

	if (ret == 0) {
		/* start the firmware */
		if ((ret = dib0700_jumpram(udev, 0x70000000)) == 0) {
			info("firmware started successfully.");
			msleep(500);
		}
	} else
		ret = -EIO;

	/* the number of ts packet has to be at least 1 */
	if (nb_packet_buffer_size < 1)
		nb_packet_buffer_size = 1;

	/* get the fimware version */
	usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
				  REQUEST_GET_VERSION,
				  USB_TYPE_VENDOR | USB_DIR_IN, 0, 0,
				  b, sizeof(b), USB_CTRL_GET_TIMEOUT);
	fw_version = (b[8] << 24) | (b[9] << 16) | (b[10] << 8) | b[11];

	/* set the buffer size - DVB-USB is allocating URB buffers
	 * only after the firwmare download was successful */
	for (i = 0; i < dib0700_device_count; i++) {
		for (adap_num = 0; adap_num < dib0700_devices[i].num_adapters;
				adap_num++) {
			if (fw_version >= 0x10201) {
				dib0700_devices[i].adapter[adap_num].stream.u.bulk.buffersize = 188*nb_packet_buffer_size;
			} else {
				/* for fw version older than 1.20.1,
				 * the buffersize has to be n times 512 */
				dib0700_devices[i].adapter[adap_num].stream.u.bulk.buffersize = ((188*nb_packet_buffer_size+188/2)/512)*512;
				if (dib0700_devices[i].adapter[adap_num].stream.u.bulk.buffersize < 512)
					dib0700_devices[i].adapter[adap_num].stream.u.bulk.buffersize = 512;
			}
		}
	}

	return ret;
}