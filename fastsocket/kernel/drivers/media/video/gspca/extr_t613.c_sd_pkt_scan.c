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
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int FIRST_PACKET ; 
 int INTER_PACKET ; 
 int LAST_PACKET ; 
 int /*<<< orphan*/  gspca_frame_add (struct gspca_dev*,int,int*,int) ; 

__attribute__((used)) static void sd_pkt_scan(struct gspca_dev *gspca_dev,
			u8 *data,			/* isoc packet */
			int len)			/* iso packet length */
{
	int pkt_type;

	if (data[0] == 0x5a) {
		/* Control Packet, after this came the header again,
		 * but extra bytes came in the packet before this,
		 * sometimes an EOF arrives, sometimes not... */
		return;
	}
	data += 2;
	len -= 2;
	if (data[0] == 0xff && data[1] == 0xd8)
		pkt_type = FIRST_PACKET;
	else if (data[len - 2] == 0xff && data[len - 1] == 0xd9)
		pkt_type = LAST_PACKET;
	else
		pkt_type = INTER_PACKET;
	gspca_frame_add(gspca_dev, pkt_type, data, len);
}