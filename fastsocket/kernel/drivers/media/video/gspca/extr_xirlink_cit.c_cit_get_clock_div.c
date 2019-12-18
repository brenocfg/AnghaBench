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
struct gspca_dev {int width; int height; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_PROBE ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int,int,int,int,int) ; 
 int cit_get_packet_size (struct gspca_dev*) ; 

__attribute__((used)) static int cit_get_clock_div(struct gspca_dev *gspca_dev)
{
	int clock_div = 7; /* 0=30 1=25 2=20 3=15 4=12 5=7.5 6=6 7=3fps ?? */
	int fps[8] = { 30, 25, 20, 15, 12, 8, 6, 3 };
	int packet_size;

	packet_size = cit_get_packet_size(gspca_dev);
	if (packet_size < 0)
		return packet_size;

	while (clock_div > 3 &&
			1000 * packet_size >
			gspca_dev->width * gspca_dev->height *
			fps[clock_div - 1] * 3 / 2)
		clock_div--;

	PDEBUG(D_PROBE,
	       "PacketSize: %d, res: %dx%d -> using clockdiv: %d (%d fps)",
	       packet_size, gspca_dev->width, gspca_dev->height, clock_div,
	       fps[clock_div]);

	return clock_div;
}