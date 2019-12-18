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
struct dmx_section_feed {scalar_t__ secbufp; scalar_t__ tsfeedp; int* secbuf; int seclen; int* secbuf_base; } ;
struct TYPE_2__ {struct dmx_section_feed sec; } ;
struct dvb_demux_feed {TYPE_1__ feed; } ;

/* Variables and functions */
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void dvb_dmx_swfilter_section_new(struct dvb_demux_feed *feed)
{
	struct dmx_section_feed *sec = &feed->feed.sec;

#ifdef DVB_DEMUX_SECTION_LOSS_LOG
	if (sec->secbufp < sec->tsfeedp) {
		int i, n = sec->tsfeedp - sec->secbufp;

		/*
		 * Section padding is done with 0xff bytes entirely.
		 * Due to speed reasons, we won't check all of them
		 * but just first and last.
		 */
		if (sec->secbuf[0] != 0xff || sec->secbuf[n - 1] != 0xff) {
			printk("dvb_demux.c section ts padding loss: %d/%d\n",
			       n, sec->tsfeedp);
			printk("dvb_demux.c pad data:");
			for (i = 0; i < n; i++)
				printk(" %02x", sec->secbuf[i]);
			printk("\n");
		}
	}
#endif

	sec->tsfeedp = sec->secbufp = sec->seclen = 0;
	sec->secbuf = sec->secbuf_base;
}