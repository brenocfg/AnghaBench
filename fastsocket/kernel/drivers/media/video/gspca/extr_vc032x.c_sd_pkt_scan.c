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
struct sd {scalar_t__ bridge; scalar_t__ image_offset; } ;
struct gspca_dev {int image_len; int frsz; } ;

/* Variables and functions */
 scalar_t__ BRIDGE_VC0321 ; 
 int /*<<< orphan*/  D_PACK ; 
 int /*<<< orphan*/  FIRST_PACKET ; 
 int /*<<< orphan*/  INTER_PACKET ; 
 int /*<<< orphan*/  LAST_PACKET ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gspca_frame_add (struct gspca_dev*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void sd_pkt_scan(struct gspca_dev *gspca_dev,
			u8 *data,			/* isoc packet */
			int len)			/* iso pkt length */
{
	struct sd *sd = (struct sd *) gspca_dev;

	if (data[0] == 0xff && data[1] == 0xd8) {
		PDEBUG(D_PACK,
			"vc032x header packet found len %d", len);
		gspca_frame_add(gspca_dev, LAST_PACKET, NULL, 0);
		data += sd->image_offset;
		len -= sd->image_offset;
		gspca_frame_add(gspca_dev, FIRST_PACKET, data, len);
		return;
	}

	/* The vc0321 sends some additional data after sending the complete
	 * frame, we ignore this. */
	if (sd->bridge == BRIDGE_VC0321) {
		int size, l;

		l = gspca_dev->image_len;
		size = gspca_dev->frsz;
		if (len > size - l)
			len = size - l;
	}
	gspca_frame_add(gspca_dev, INTER_PACKET, data, len);
}