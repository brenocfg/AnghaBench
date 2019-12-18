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
struct sd {scalar_t__ bridge; int to_skip; } ;
struct gspca_dev {int width; int /*<<< orphan*/  last_packet_type; } ;

/* Variables and functions */
 scalar_t__ BRIDGE_ST6422 ; 
 int /*<<< orphan*/  DISCARD_PACKET ; 
 int /*<<< orphan*/  D_ERR ; 
 int /*<<< orphan*/  D_PACK ; 
 int /*<<< orphan*/  FIRST_PACKET ; 
 int /*<<< orphan*/  INTER_PACKET ; 
 int /*<<< orphan*/  LAST_PACKET ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gspca_frame_add (struct gspca_dev*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void stv06xx_pkt_scan(struct gspca_dev *gspca_dev,
			u8 *data,			/* isoc packet */
			int len)			/* iso packet length */
{
	struct sd *sd = (struct sd *) gspca_dev;

	PDEBUG(D_PACK, "Packet of length %d arrived", len);

	/* A packet may contain several frames
	   loop until the whole packet is reached */
	while (len) {
		int id, chunk_len;

		if (len < 4) {
			PDEBUG(D_PACK, "Packet is smaller than 4 bytes");
			return;
		}

		/* Capture the id */
		id = (data[0] << 8) | data[1];

		/* Capture the chunk length */
		chunk_len = (data[2] << 8) | data[3];
		PDEBUG(D_PACK, "Chunk id: %x, length: %d", id, chunk_len);

		data += 4;
		len -= 4;

		if (len < chunk_len) {
			PDEBUG(D_ERR, "URB packet length is smaller"
				" than the specified chunk length");
			gspca_dev->last_packet_type = DISCARD_PACKET;
			return;
		}

		/* First byte seem to be 02=data 2nd byte is unknown??? */
		if (sd->bridge == BRIDGE_ST6422 && (id & 0xff00) == 0x0200)
			goto frame_data;

		switch (id) {
		case 0x0200:
		case 0x4200:
frame_data:
			PDEBUG(D_PACK, "Frame data packet detected");

			if (sd->to_skip) {
				int skip = (sd->to_skip < chunk_len) ?
					    sd->to_skip : chunk_len;
				data += skip;
				len -= skip;
				chunk_len -= skip;
				sd->to_skip -= skip;
			}

			gspca_frame_add(gspca_dev, INTER_PACKET,
					data, chunk_len);
			break;

		case 0x8001:
		case 0x8005:
		case 0xc001:
		case 0xc005:
			PDEBUG(D_PACK, "Starting new frame");

			/* Create a new frame, chunk length should be zero */
			gspca_frame_add(gspca_dev, FIRST_PACKET,
					NULL, 0);

			if (sd->bridge == BRIDGE_ST6422)
				sd->to_skip = gspca_dev->width * 4;

			if (chunk_len)
				PDEBUG(D_ERR, "Chunk length is "
					      "non-zero on a SOF");
			break;

		case 0x8002:
		case 0x8006:
		case 0xc002:
			PDEBUG(D_PACK, "End of frame detected");

			/* Complete the last frame (if any) */
			gspca_frame_add(gspca_dev, LAST_PACKET,
					NULL, 0);

			if (chunk_len)
				PDEBUG(D_ERR, "Chunk length is "
					      "non-zero on a EOF");
			break;

		case 0x0005:
			PDEBUG(D_PACK, "Chunk 0x005 detected");
			/* Unknown chunk with 11 bytes of data,
			   occurs just before end of each frame
			   in compressed mode */
			break;

		case 0x0100:
			PDEBUG(D_PACK, "Chunk 0x0100 detected");
			/* Unknown chunk with 2 bytes of data,
			   occurs 2-3 times per USB interrupt */
			break;
		case 0x42ff:
			PDEBUG(D_PACK, "Chunk 0x42ff detected");
			/* Special chunk seen sometimes on the ST6422 */
			break;
		default:
			PDEBUG(D_PACK, "Unknown chunk 0x%04x detected", id);
			/* Unknown chunk */
		}
		data    += chunk_len;
		len     -= chunk_len;
	}
}