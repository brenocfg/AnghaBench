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
struct TYPE_5__ {int nr_bufs; int nr_packets; int /*<<< orphan*/  pt_ts; } ;
struct TYPE_6__ {unsigned long data; int /*<<< orphan*/  function; } ;
struct TYPE_4__ {int need_two; struct saa7134_dev* dev; TYPE_3__ timeout; int /*<<< orphan*/  queue; } ;
struct saa7134_dev {TYPE_2__ ts; int /*<<< orphan*/  pci; scalar_t__ ts_started; TYPE_1__ ts_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int VIDEO_MAX_FRAME ; 
 int /*<<< orphan*/  init_timer (TYPE_3__*) ; 
 int /*<<< orphan*/  saa7134_buffer_timeout ; 
 int /*<<< orphan*/  saa7134_pgtable_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  saa7134_ts_init_hw (struct saa7134_dev*) ; 
 int ts_nr_packets ; 
 int tsbufs ; 

int saa7134_ts_init1(struct saa7134_dev *dev)
{
	/* sanitycheck insmod options */
	if (tsbufs < 2)
		tsbufs = 2;
	if (tsbufs > VIDEO_MAX_FRAME)
		tsbufs = VIDEO_MAX_FRAME;
	if (ts_nr_packets < 4)
		ts_nr_packets = 4;
	if (ts_nr_packets > 312)
		ts_nr_packets = 312;
	dev->ts.nr_bufs    = tsbufs;
	dev->ts.nr_packets = ts_nr_packets;

	INIT_LIST_HEAD(&dev->ts_q.queue);
	init_timer(&dev->ts_q.timeout);
	dev->ts_q.timeout.function = saa7134_buffer_timeout;
	dev->ts_q.timeout.data     = (unsigned long)(&dev->ts_q);
	dev->ts_q.dev              = dev;
	dev->ts_q.need_two         = 1;
	dev->ts_started            = 0;
	saa7134_pgtable_alloc(dev->pci,&dev->ts.pt_ts);

	/* init TS hw */
	saa7134_ts_init_hw(dev);

	return 0;
}