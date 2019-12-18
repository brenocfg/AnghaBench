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
struct flexcop_usb {int tmp_buffer_length; int* tmp_buffer; int /*<<< orphan*/  fc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  deb_ts (char*,...) ; 
 int /*<<< orphan*/  flexcop_pass_dmx_packets (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

__attribute__((used)) static void flexcop_usb_process_frame(struct flexcop_usb *fc_usb,
	u8 *buffer, int buffer_length)
{
	u8 *b;
	int l;

	deb_ts("tmp_buffer_length=%d, buffer_length=%d\n",
		fc_usb->tmp_buffer_length, buffer_length);

	if (fc_usb->tmp_buffer_length > 0) {
		memcpy(fc_usb->tmp_buffer+fc_usb->tmp_buffer_length, buffer,
				buffer_length);
		fc_usb->tmp_buffer_length += buffer_length;
		b = fc_usb->tmp_buffer;
		l = fc_usb->tmp_buffer_length;
	} else {
		b=buffer;
		l=buffer_length;
	}

	while (l >= 190) {
		if (*b == 0xff) {
			switch (*(b+1) & 0x03) {
			case 0x01: /* media packet */
				if (*(b+2) == 0x47)
					flexcop_pass_dmx_packets(
							fc_usb->fc_dev, b+2, 1);
				else
					deb_ts(
					"not ts packet %02x %02x %02x %02x \n",
						*(b+2), *(b+3),
						*(b+4), *(b+5));
				b += 190;
				l -= 190;
				break;
			default:
				deb_ts("wrong packet type\n");
				l = 0;
				break;
			}
		} else {
			deb_ts("wrong header\n");
			l = 0;
		}
	}

	if (l>0)
		memcpy(fc_usb->tmp_buffer, b, l);
	fc_usb->tmp_buffer_length = l;
}