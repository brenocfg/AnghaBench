#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dvb_demux_filter {struct dvb_demux_filter* next; } ;
struct dmx_section_feed {int* secbuf; scalar_t__ seclen; scalar_t__ is_filtering; scalar_t__ check_crc; } ;
struct TYPE_2__ {struct dmx_section_feed sec; } ;
struct dvb_demux_feed {TYPE_1__ feed; struct dvb_demux_filter* filter; struct dvb_demux* demux; } ;
struct dvb_demux {scalar_t__ (* check_crc32 ) (struct dvb_demux_feed*,int*,scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ dvb_dmx_swfilter_sectionfilter (struct dvb_demux_feed*,struct dvb_demux_filter*) ; 
 scalar_t__ stub1 (struct dvb_demux_feed*,int*,scalar_t__) ; 

__attribute__((used)) static inline int dvb_dmx_swfilter_section_feed(struct dvb_demux_feed *feed)
{
	struct dvb_demux *demux = feed->demux;
	struct dvb_demux_filter *f = feed->filter;
	struct dmx_section_feed *sec = &feed->feed.sec;
	int section_syntax_indicator;

	if (!sec->is_filtering)
		return 0;

	if (!f)
		return 0;

	if (sec->check_crc) {
		section_syntax_indicator = ((sec->secbuf[1] & 0x80) != 0);
		if (section_syntax_indicator &&
		    demux->check_crc32(feed, sec->secbuf, sec->seclen))
			return -1;
	}

	do {
		if (dvb_dmx_swfilter_sectionfilter(feed, f) < 0)
			return -1;
	} while ((f = f->next) && sec->is_filtering);

	sec->seclen = 0;

	return 0;
}