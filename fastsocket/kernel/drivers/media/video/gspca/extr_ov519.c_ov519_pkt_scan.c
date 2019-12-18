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
struct gspca_dev {void* last_packet_type; } ;

/* Variables and functions */
 void* DISCARD_PACKET ; 
 int /*<<< orphan*/  FIRST_PACKET ; 
 int HDRSZ ; 
 int /*<<< orphan*/  INTER_PACKET ; 
 int /*<<< orphan*/  LAST_PACKET ; 
 int /*<<< orphan*/  gspca_frame_add (struct gspca_dev*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  ov51x_handle_button (struct gspca_dev*,int) ; 

__attribute__((used)) static void ov519_pkt_scan(struct gspca_dev *gspca_dev,
			u8 *data,			/* isoc packet */
			int len)			/* iso packet length */
{
	/* Header of ov519 is 16 bytes:
	 *     Byte     Value      Description
	 *	0	0xff	magic
	 *	1	0xff	magic
	 *	2	0xff	magic
	 *	3	0xXX	0x50 = SOF, 0x51 = EOF
	 *	9	0xXX	0x01 initial frame without data,
	 *			0x00 standard frame with image
	 *	14	Lo	in EOF: length of image data / 8
	 *	15	Hi
	 */

	if (data[0] == 0xff && data[1] == 0xff && data[2] == 0xff) {
		switch (data[3]) {
		case 0x50:		/* start of frame */
			/* Don't check the button state here, as the state
			   usually (always ?) changes at EOF and checking it
			   here leads to unnecessary snapshot state resets. */
#define HDRSZ 16
			data += HDRSZ;
			len -= HDRSZ;
#undef HDRSZ
			if (data[0] == 0xff || data[1] == 0xd8)
				gspca_frame_add(gspca_dev, FIRST_PACKET,
						data, len);
			else
				gspca_dev->last_packet_type = DISCARD_PACKET;
			return;
		case 0x51:		/* end of frame */
			ov51x_handle_button(gspca_dev, data[11] & 1);
			if (data[9] != 0)
				gspca_dev->last_packet_type = DISCARD_PACKET;
			gspca_frame_add(gspca_dev, LAST_PACKET,
					NULL, 0);
			return;
		}
	}

	/* intermediate packet */
	gspca_frame_add(gspca_dev, INTER_PACKET, data, len);
}