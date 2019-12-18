#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_3__ {int /*<<< orphan*/  ts; } ;
struct TYPE_4__ {int (* ts ) (int const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct dvb_demux_feed {int peslen; TYPE_1__ feed; TYPE_2__ cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMX_OK ; 
 int payload (int const*) ; 
 int stub1 (int const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int dvb_dmx_swfilter_payload(struct dvb_demux_feed *feed,
					   const u8 *buf)
{
	int count = payload(buf);
	int p;
	//int ccok;
	//u8 cc;

	if (count == 0)
		return -1;

	p = 188 - count;

	/*
	cc = buf[3] & 0x0f;
	ccok = ((feed->cc + 1) & 0x0f) == cc;
	feed->cc = cc;
	if (!ccok)
		printk("missed packet!\n");
	*/

	if (buf[1] & 0x40)	// PUSI ?
		feed->peslen = 0xfffa;

	feed->peslen += count;

	return feed->cb.ts(&buf[p], count, NULL, 0, &feed->feed.ts, DMX_OK);
}