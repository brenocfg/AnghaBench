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
struct sd {scalar_t__ packet_nr; } ;
struct gspca_dev {int width; int height; int /*<<< orphan*/  last_packet_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISCARD_PACKET ; 
 int /*<<< orphan*/  D_ERR ; 
 int /*<<< orphan*/  FIRST_PACKET ; 
 int /*<<< orphan*/  INTER_PACKET ; 
 int /*<<< orphan*/  LAST_PACKET ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 int /*<<< orphan*/  gspca_frame_add (struct gspca_dev*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  ov51x_handle_button (struct gspca_dev*,int) ; 

__attribute__((used)) static void ov511_pkt_scan(struct gspca_dev *gspca_dev,
			u8 *in,			/* isoc packet */
			int len)		/* iso packet length */
{
	struct sd *sd = (struct sd *) gspca_dev;

	/* SOF/EOF packets have 1st to 8th bytes zeroed and the 9th
	 * byte non-zero. The EOF packet has image width/height in the
	 * 10th and 11th bytes. The 9th byte is given as follows:
	 *
	 * bit 7: EOF
	 *     6: compression enabled
	 *     5: 422/420/400 modes
	 *     4: 422/420/400 modes
	 *     3: 1
	 *     2: snapshot button on
	 *     1: snapshot frame
	 *     0: even/odd field
	 */
	if (!(in[0] | in[1] | in[2] | in[3] | in[4] | in[5] | in[6] | in[7]) &&
	    (in[8] & 0x08)) {
		ov51x_handle_button(gspca_dev, (in[8] >> 2) & 1);
		if (in[8] & 0x80) {
			/* Frame end */
			if ((in[9] + 1) * 8 != gspca_dev->width ||
			    (in[10] + 1) * 8 != gspca_dev->height) {
				PDEBUG(D_ERR, "Invalid frame size, got: %dx%d,"
					" requested: %dx%d\n",
					(in[9] + 1) * 8, (in[10] + 1) * 8,
					gspca_dev->width, gspca_dev->height);
				gspca_dev->last_packet_type = DISCARD_PACKET;
				return;
			}
			/* Add 11 byte footer to frame, might be usefull */
			gspca_frame_add(gspca_dev, LAST_PACKET, in, 11);
			return;
		} else {
			/* Frame start */
			gspca_frame_add(gspca_dev, FIRST_PACKET, in, 0);
			sd->packet_nr = 0;
		}
	}

	/* Ignore the packet number */
	len--;

	/* intermediate packet */
	gspca_frame_add(gspca_dev, INTER_PACKET, in, len);
}