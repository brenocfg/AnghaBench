#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_8__ {int /*<<< orphan*/  secbufp; int /*<<< orphan*/  seclen; int /*<<< orphan*/  is_filtering; } ;
struct TYPE_10__ {int /*<<< orphan*/  is_filtering; } ;
struct TYPE_9__ {TYPE_3__ sec; TYPE_5__ ts; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* ts ) (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ) ;} ;
struct dvb_demux_feed {int type; int ts_type; TYPE_4__ feed; TYPE_2__* demux; TYPE_1__ cb; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* write_to_decoder ) (struct dvb_demux_feed*,int /*<<< orphan*/  const*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DMX_OK ; 
#define  DMX_TYPE_SEC 129 
#define  DMX_TYPE_TS 128 
 int TS_DECODER ; 
 int TS_PACKET ; 
 int TS_PAYLOAD_ONLY ; 
 int /*<<< orphan*/  dvb_dmx_swfilter_payload (struct dvb_demux_feed*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  dvb_dmx_swfilter_section_packet (struct dvb_demux_feed*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct dvb_demux_feed*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static inline void dvb_dmx_swfilter_packet_type(struct dvb_demux_feed *feed,
						const u8 *buf)
{
	switch (feed->type) {
	case DMX_TYPE_TS:
		if (!feed->feed.ts.is_filtering)
			break;
		if (feed->ts_type & TS_PACKET) {
			if (feed->ts_type & TS_PAYLOAD_ONLY)
				dvb_dmx_swfilter_payload(feed, buf);
			else
				feed->cb.ts(buf, 188, NULL, 0, &feed->feed.ts,
					    DMX_OK);
		}
		if (feed->ts_type & TS_DECODER)
			if (feed->demux->write_to_decoder)
				feed->demux->write_to_decoder(feed, buf, 188);
		break;

	case DMX_TYPE_SEC:
		if (!feed->feed.sec.is_filtering)
			break;
		if (dvb_dmx_swfilter_section_packet(feed, buf) < 0)
			feed->feed.sec.seclen = feed->feed.sec.secbufp = 0;
		break;

	default:
		break;
	}
}