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
struct sd {int* jpeg_hdr; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIRST_PACKET ; 
 int /*<<< orphan*/  INTER_PACKET ; 
 int JPEG_HDR_SZ ; 
 int /*<<< orphan*/  LAST_PACKET ; 
 scalar_t__ STKHDRSZ ; 
 int /*<<< orphan*/  gspca_frame_add (struct gspca_dev*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void sd_pkt_scan(struct gspca_dev *gspca_dev,
			u8 *data,			/* isoc packet */
			int len)			/* iso packet length */
{
	struct sd *sd = (struct sd *) gspca_dev;
	static unsigned char ffd9[] = {0xff, 0xd9};

	/* a frame starts with:
	 *	- 0xff 0xfe
	 *	- 0x08 0x00	- length (little endian ?!)
	 *	- 4 bytes = size of whole frame (BE - including header)
	 *	- 0x00 0x0c
	 *	- 0xff 0xd8
	 *	- ..	JPEG image with escape sequences (ff 00)
	 *		(without ending - ff d9)
	 */
	if (data[0] == 0xff && data[1] == 0xfe) {
		gspca_frame_add(gspca_dev, LAST_PACKET,
				ffd9, 2);

		/* put the JPEG 411 header */
		gspca_frame_add(gspca_dev, FIRST_PACKET,
			sd->jpeg_hdr, JPEG_HDR_SZ);

		/* beginning of the frame */
#define STKHDRSZ 12
		data += STKHDRSZ;
		len -= STKHDRSZ;
	}
	gspca_frame_add(gspca_dev, INTER_PACKET, data, len);
}