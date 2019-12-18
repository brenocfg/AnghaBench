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
struct ttusb {scalar_t__ running_feed_count; } ;
struct dvb_demux_feed {int /*<<< orphan*/  index; scalar_t__ demux; } ;

/* Variables and functions */
 int /*<<< orphan*/  ttusb_del_channel (struct ttusb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttusb_stop_iso_xfer (struct ttusb*) ; 

__attribute__((used)) static int ttusb_stop_feed(struct dvb_demux_feed *dvbdmxfeed)
{
	struct ttusb *ttusb = (struct ttusb *) dvbdmxfeed->demux;

	ttusb_del_channel(ttusb, dvbdmxfeed->index);

	if (--ttusb->running_feed_count == 0)
		ttusb_stop_iso_xfer(ttusb);

	return 0;
}