#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int dma; } ;
struct TYPE_5__ {int nr_packets; TYPE_1__ pt_ts; } ;
struct saa7134_dev {int ts_started; size_t board; TYPE_2__ ts; } ;
struct TYPE_6__ {int ts_type; int ts_force_val; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
#define  SAA7134_MPEG_TS_PARALLEL 129 
#define  SAA7134_MPEG_TS_SERIAL 128 
 int /*<<< orphan*/  SAA7134_RS_CONTROL (int) ; 
 int SAA7134_RS_CONTROL_BURST_16 ; 
 int SAA7134_RS_CONTROL_ME ; 
 int /*<<< orphan*/  SAA7134_RS_PITCH (int) ; 
 int /*<<< orphan*/  SAA7134_TS_DMA0 ; 
 int /*<<< orphan*/  SAA7134_TS_DMA1 ; 
 int /*<<< orphan*/  SAA7134_TS_DMA2 ; 
 int /*<<< orphan*/  SAA7134_TS_PARALLEL ; 
 int /*<<< orphan*/  SAA7134_TS_PARALLEL_SERIAL ; 
 int /*<<< orphan*/  SAA7134_TS_SERIAL0 ; 
 int /*<<< orphan*/  SAA7134_TS_SERIAL1 ; 
 int TS_PACKET_SIZE ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 TYPE_3__* saa7134_boards ; 
 int /*<<< orphan*/  saa_writeb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  saa_writel (int /*<<< orphan*/ ,int) ; 

int saa7134_ts_start(struct saa7134_dev *dev)
{
	dprintk("TS start\n");

	BUG_ON(dev->ts_started);

	/* dma: setup channel 5 (= TS) */
	saa_writeb(SAA7134_TS_DMA0, (dev->ts.nr_packets - 1) & 0xff);
	saa_writeb(SAA7134_TS_DMA1,
		((dev->ts.nr_packets - 1) >> 8) & 0xff);
	/* TSNOPIT=0, TSCOLAP=0 */
	saa_writeb(SAA7134_TS_DMA2,
		(((dev->ts.nr_packets - 1) >> 16) & 0x3f) | 0x00);
	saa_writel(SAA7134_RS_PITCH(5), TS_PACKET_SIZE);
	saa_writel(SAA7134_RS_CONTROL(5), SAA7134_RS_CONTROL_BURST_16 |
					  SAA7134_RS_CONTROL_ME |
					  (dev->ts.pt_ts.dma >> 12));

	/* reset hardware TS buffers */
	saa_writeb(SAA7134_TS_SERIAL1, 0x00);
	saa_writeb(SAA7134_TS_SERIAL1, 0x03);
	saa_writeb(SAA7134_TS_SERIAL1, 0x00);
	saa_writeb(SAA7134_TS_SERIAL1, 0x01);

	/* TS clock non-inverted */
	saa_writeb(SAA7134_TS_SERIAL1, 0x00);

	/* Start TS stream */
	switch (saa7134_boards[dev->board].ts_type) {
	case SAA7134_MPEG_TS_PARALLEL:
		saa_writeb(SAA7134_TS_SERIAL0, 0x40);
		saa_writeb(SAA7134_TS_PARALLEL, 0xec |
			(saa7134_boards[dev->board].ts_force_val << 4));
		break;
	case SAA7134_MPEG_TS_SERIAL:
		saa_writeb(SAA7134_TS_SERIAL0, 0xd8);
		saa_writeb(SAA7134_TS_PARALLEL, 0x6c |
			(saa7134_boards[dev->board].ts_force_val << 4));
		saa_writeb(SAA7134_TS_PARALLEL_SERIAL, 0xbc);
		saa_writeb(SAA7134_TS_SERIAL1, 0x02);
		break;
	}

	dev->ts_started = 1;

	return 0;
}