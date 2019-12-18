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
typedef  int /*<<< orphan*/  u8 ;
struct sd {int packet; } ;
struct gspca_dev {int height; int width; scalar_t__ empty_packet; } ;

/* Variables and functions */
 int FIRST_PACKET ; 
 int INTER_PACKET ; 
 int LAST_PACKET ; 
 int /*<<< orphan*/  gspca_frame_add (struct gspca_dev*,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void sd_pkt_scan(struct gspca_dev *gspca_dev,
			u8 *data,			/* isoc packet */
			int len)			/* iso packet length */
{
	struct sd *sd = (struct sd *) gspca_dev;
	int packet_type0, packet_type1;

	packet_type0 = packet_type1 = INTER_PACKET;
	if (gspca_dev->empty_packet) {
		gspca_dev->empty_packet = 0;
		sd->packet = gspca_dev->height / 2;
		packet_type0 = FIRST_PACKET;
	} else if (sd->packet == 0)
		return;			/* 2 more lines in 352x288 ! */
	sd->packet--;
	if (sd->packet == 0)
		packet_type1 = LAST_PACKET;

	/* each packet contains:
	 * - header 2 bytes
	 * - RGRG line
	 * - 4 bytes
	 * - GBGB line
	 * - 4 bytes
	 */
	gspca_frame_add(gspca_dev, packet_type0,
			data + 2, gspca_dev->width);
	gspca_frame_add(gspca_dev, packet_type1,
			data + gspca_dev->width + 5, gspca_dev->width);
}