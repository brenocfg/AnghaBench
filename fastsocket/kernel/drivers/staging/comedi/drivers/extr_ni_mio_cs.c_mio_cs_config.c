#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_16__ ;
typedef  struct TYPE_20__   TYPE_11__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_short ;
struct TYPE_28__ {int TupleDataMax; void* Attributes; int /*<<< orphan*/  DesiredTuple; scalar_t__ TupleOffset; int /*<<< orphan*/ * TupleData; } ;
typedef  TYPE_7__ tuple_t ;
struct TYPE_20__ {int ConfigIndex; int /*<<< orphan*/  Present; int /*<<< orphan*/  ConfigBase; } ;
struct TYPE_30__ {int IRQInfo1; int IRQInfo2; } ;
struct TYPE_19__ {int NumPorts1; int IOAddrLines; int BasePort1; scalar_t__ NumPorts2; int /*<<< orphan*/  Attributes1; } ;
struct pcmcia_device {int /*<<< orphan*/ * dev_node; TYPE_11__ conf; TYPE_9__ irq; TYPE_10__ io; } ;
struct TYPE_26__ {int IRQInfo1; int IRQInfo2; } ;
struct TYPE_25__ {int flags; int nwin; TYPE_3__* win; } ;
struct TYPE_23__ {int flags; int nwin; } ;
struct TYPE_27__ {int index; int flags; int subtuples; TYPE_5__ irq; TYPE_4__ io; TYPE_2__ mem; } ;
struct TYPE_22__ {int /*<<< orphan*/ * rmask; int /*<<< orphan*/  base; } ;
struct TYPE_29__ {TYPE_6__ cftable_entry; TYPE_1__ config; } ;
typedef  TYPE_8__ cisparse_t ;
typedef  int /*<<< orphan*/  cisdata_t ;
struct TYPE_24__ {int base; int len; } ;
struct TYPE_21__ {int /*<<< orphan*/  (* multi ) (int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CISTPL_CFTABLE_ENTRY ; 
 int /*<<< orphan*/  CISTPL_CONFIG ; 
 int CISTPL_IO_LINES_MASK ; 
 int /*<<< orphan*/  CISTPL_LONGLINK_MFC ; 
 int /*<<< orphan*/  CISTPL_MANFID ; 
 int /*<<< orphan*/  DPRINTK (char*,struct pcmcia_device*) ; 
 int /*<<< orphan*/  IO_DATA_PATH_WIDTH_AUTO ; 
 void* TUPLE_RETURN_COMMON ; 
 void* TUPLE_RETURN_LINK ; 
 int /*<<< orphan*/  dev_node ; 
 scalar_t__ first_tuple (struct pcmcia_device*,TYPE_7__*,TYPE_8__*) ; 
 TYPE_16__* info ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int pcmcia_get_first_tuple (struct pcmcia_device*,TYPE_7__*) ; 
 int pcmcia_get_tuple_data (struct pcmcia_device*,TYPE_7__*) ; 
 int pcmcia_parse_tuple (TYPE_7__*,TYPE_8__*) ; 
 int pcmcia_request_configuration (struct pcmcia_device*,TYPE_11__*) ; 
 int pcmcia_request_io (struct pcmcia_device*,TYPE_10__*) ; 
 int pcmcia_request_irq (struct pcmcia_device*,TYPE_9__*) ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 int /*<<< orphan*/  stub1 (int) ; 

__attribute__((used)) static void mio_cs_config(struct pcmcia_device *link)
{
	tuple_t tuple;
	u_short buf[128];
	cisparse_t parse;
	int manfid = 0, prodid = 0;
	int ret;

	DPRINTK("mio_cs_config(link=%p)\n", link);

	tuple.TupleData = (cisdata_t *) buf;
	tuple.TupleOffset = 0;
	tuple.TupleDataMax = 255;
	tuple.Attributes = 0;

	tuple.DesiredTuple = CISTPL_CONFIG;
	ret = pcmcia_get_first_tuple(link, &tuple);
	ret = pcmcia_get_tuple_data(link, &tuple);
	ret = pcmcia_parse_tuple(&tuple, &parse);
	link->conf.ConfigBase = parse.config.base;
	link->conf.Present = parse.config.rmask[0];

#if 0
	tuple.DesiredTuple = CISTPL_LONGLINK_MFC;
	tuple.Attributes = TUPLE_RETURN_COMMON | TUPLE_RETURN_LINK;
	info->multi(first_tuple(link, &tuple, &parse) == 0);
#endif

	tuple.DesiredTuple = CISTPL_MANFID;
	tuple.Attributes = TUPLE_RETURN_COMMON;
	if ((pcmcia_get_first_tuple(link, &tuple) == 0) &&
	    (pcmcia_get_tuple_data(link, &tuple) == 0)) {
		manfid = le16_to_cpu(buf[0]);
		prodid = le16_to_cpu(buf[1]);
	}
	/* printk("manfid = 0x%04x, 0x%04x\n",manfid,prodid); */

	tuple.DesiredTuple = CISTPL_CFTABLE_ENTRY;
	tuple.Attributes = 0;
	ret = pcmcia_get_first_tuple(link, &tuple);
	ret = pcmcia_get_tuple_data(link, &tuple);
	ret = pcmcia_parse_tuple(&tuple, &parse);

#if 0
	printk(" index: 0x%x\n", parse.cftable_entry.index);
	printk(" flags: 0x%x\n", parse.cftable_entry.flags);
	printk(" io flags: 0x%x\n", parse.cftable_entry.io.flags);
	printk(" io nwin: 0x%x\n", parse.cftable_entry.io.nwin);
	printk(" io base: 0x%x\n", parse.cftable_entry.io.win[0].base);
	printk(" io len: 0x%x\n", parse.cftable_entry.io.win[0].len);
	printk(" irq1: 0x%x\n", parse.cftable_entry.irq.IRQInfo1);
	printk(" irq2: 0x%x\n", parse.cftable_entry.irq.IRQInfo2);
	printk(" mem flags: 0x%x\n", parse.cftable_entry.mem.flags);
	printk(" mem nwin: 0x%x\n", parse.cftable_entry.mem.nwin);
	printk(" subtuples: 0x%x\n", parse.cftable_entry.subtuples);
#endif

#if 0
	link->io.NumPorts1 = 0x20;
	link->io.IOAddrLines = 5;
	link->io.Attributes1 = IO_DATA_PATH_WIDTH_AUTO;
#endif
	link->io.NumPorts1 = parse.cftable_entry.io.win[0].len;
	link->io.IOAddrLines =
	    parse.cftable_entry.io.flags & CISTPL_IO_LINES_MASK;
	link->io.NumPorts2 = 0;

	{
		int base;
		for (base = 0x000; base < 0x400; base += 0x20) {
			link->io.BasePort1 = base;
			ret = pcmcia_request_io(link, &link->io);
			/* printk("RequestIO 0x%02x\n",ret); */
			if (!ret)
				break;
		}
	}

	link->irq.IRQInfo1 = parse.cftable_entry.irq.IRQInfo1;
	link->irq.IRQInfo2 = parse.cftable_entry.irq.IRQInfo2;
	ret = pcmcia_request_irq(link, &link->irq);
	if (ret) {
		printk("pcmcia_request_irq() returned error: %i\n", ret);
	}
	/* printk("RequestIRQ 0x%02x\n",ret); */

	link->conf.ConfigIndex = 1;

	ret = pcmcia_request_configuration(link, &link->conf);
	/* printk("RequestConfiguration %d\n",ret); */

	link->dev_node = &dev_node;
}