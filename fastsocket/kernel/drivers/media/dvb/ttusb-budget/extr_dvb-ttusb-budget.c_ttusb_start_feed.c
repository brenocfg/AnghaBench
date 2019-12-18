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
struct ttusb {int /*<<< orphan*/  running_feed_count; } ;
struct dvb_demux_feed {int type; int pes_type; int /*<<< orphan*/  pid; int /*<<< orphan*/  index; scalar_t__ demux; } ;

/* Variables and functions */
#define  DMX_TS_PES_AUDIO 134 
#define  DMX_TS_PES_OTHER 133 
#define  DMX_TS_PES_PCR 132 
#define  DMX_TS_PES_TELETEXT 131 
#define  DMX_TS_PES_VIDEO 130 
#define  DMX_TYPE_SEC 129 
#define  DMX_TYPE_TS 128 
 int EINVAL ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  ttusb_set_channel (struct ttusb*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttusb_start_iso_xfer (struct ttusb*) ; 

__attribute__((used)) static int ttusb_start_feed(struct dvb_demux_feed *dvbdmxfeed)
{
	struct ttusb *ttusb = (struct ttusb *) dvbdmxfeed->demux;
	int feed_type = 1;

	dprintk("ttusb_start_feed\n");

	switch (dvbdmxfeed->type) {
	case DMX_TYPE_TS:
		break;
	case DMX_TYPE_SEC:
		break;
	default:
		return -EINVAL;
	}

	if (dvbdmxfeed->type == DMX_TYPE_TS) {
		switch (dvbdmxfeed->pes_type) {
		case DMX_TS_PES_VIDEO:
		case DMX_TS_PES_AUDIO:
		case DMX_TS_PES_TELETEXT:
		case DMX_TS_PES_PCR:
		case DMX_TS_PES_OTHER:
			break;
		default:
			return -EINVAL;
		}
	}

#ifdef TTUSB_HWSECTIONS
#error TODO: allocate filters
	if (dvbdmxfeed->type == DMX_TYPE_TS) {
		feed_type = 1;
	} else if (dvbdmxfeed->type == DMX_TYPE_SEC) {
		feed_type = 2;
	}
#endif

	ttusb_set_channel(ttusb, dvbdmxfeed->index, feed_type, dvbdmxfeed->pid);

	if (0 == ttusb->running_feed_count++)
		ttusb_start_iso_xfer(ttusb);

	return 0;
}