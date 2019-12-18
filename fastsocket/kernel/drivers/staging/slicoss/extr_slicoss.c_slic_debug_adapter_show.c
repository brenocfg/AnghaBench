#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint ;
typedef  scalar_t__ u32 ;
struct seq_file {struct adapter* private; } ;
struct TYPE_14__ {scalar_t__ IpHlen; scalar_t__ IpLen; scalar_t__ IpCsum; scalar_t__ TpHlen; scalar_t__ TpCsum; scalar_t__ Code; scalar_t__ Drbl; scalar_t__ Crc; scalar_t__ Invp; scalar_t__ Longe; scalar_t__ Carre; scalar_t__ Bufov; scalar_t__ rcvearly; scalar_t__ uflow802; scalar_t__ Tprtoflow; scalar_t__ oflow802; } ;
struct TYPE_12__ {scalar_t__ xmit_collisions; scalar_t__ xmt_errors; scalar_t__ rcv_discards; scalar_t__ rcv_errors; } ;
struct TYPE_13__ {TYPE_5__ iface; } ;
struct TYPE_11__ {scalar_t__ multicast; scalar_t__ tx_bytes; scalar_t__ tx_packets; scalar_t__ rx_bytes; scalar_t__ rx_packets; } ;
struct TYPE_10__ {scalar_t__ count; } ;
struct adapter {TYPE_7__ if_events; scalar_t__ isr_reg_writes; scalar_t__ icr_reg_writes; scalar_t__ all_reg_writes; scalar_t__ false_interrupts; scalar_t__ num_isrs; scalar_t__ upr_interrupts; scalar_t__ linkevent_interrupts; scalar_t__ xmit_interrupts; scalar_t__ rcv_interrupts; scalar_t__ error_rmiss_interrupts; scalar_t__ error_interrupts; scalar_t__ max_isr_xmits; scalar_t__ rcv_interrupt_yields; scalar_t__ max_isr_rcvs; TYPE_6__ slic_stats; TYPE_4__ stats; scalar_t__ rcv_drops; scalar_t__ rcv_unicasts; scalar_t__ rcv_multicasts; scalar_t__ rcv_broadcasts; TYPE_3__ rcvqueue; TYPE_2__* card; scalar_t__ irq; int /*<<< orphan*/  linkduplex; int /*<<< orphan*/  linkspeed; scalar_t__ physport; int /*<<< orphan*/  linkstate; TYPE_1__* netdev; } ;
struct TYPE_9__ {scalar_t__ loadlevel_current; } ;
struct TYPE_8__ {scalar_t__ name; } ;

/* Variables and functions */
 scalar_t__ SLIC_DUPLEX (int /*<<< orphan*/ ) ; 
 scalar_t__ SLIC_LINKSTATE (int /*<<< orphan*/ ) ; 
 scalar_t__ SLIC_RCVQ_ENTRIES ; 
 scalar_t__ SLIC_SPEED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,scalar_t__) ; 

__attribute__((used)) static int slic_debug_adapter_show(struct seq_file *seq, void *v)
{
	struct adapter *adapter = seq->private;

	if ((adapter->netdev) && (adapter->netdev->name)) {
		seq_printf(seq, "info: interface          : %s\n",
			    adapter->netdev->name);
	}
	seq_printf(seq, "info: status             : %s\n",
		SLIC_LINKSTATE(adapter->linkstate));
	seq_printf(seq, "info: port               : %d\n",
		adapter->physport);
	seq_printf(seq, "info: speed              : %s\n",
		SLIC_SPEED(adapter->linkspeed));
	seq_printf(seq, "info: duplex             : %s\n",
		SLIC_DUPLEX(adapter->linkduplex));
	seq_printf(seq, "info: irq                : 0x%X\n",
		(uint) adapter->irq);
	seq_printf(seq, "info: Interrupt Agg Delay: %d usec\n",
		adapter->card->loadlevel_current);
	seq_printf(seq, "info: RcvQ max entries   : %4.4X\n",
		SLIC_RCVQ_ENTRIES);
	seq_printf(seq, "info: RcvQ current       : %4.4X\n",
		    adapter->rcvqueue.count);
	seq_printf(seq, "rx stats: packets                  : %8.8lX\n",
		    adapter->stats.rx_packets);
	seq_printf(seq, "rx stats: bytes                    : %8.8lX\n",
		    adapter->stats.rx_bytes);
	seq_printf(seq, "rx stats: broadcasts               : %8.8X\n",
		    adapter->rcv_broadcasts);
	seq_printf(seq, "rx stats: multicasts               : %8.8X\n",
		    adapter->rcv_multicasts);
	seq_printf(seq, "rx stats: unicasts                 : %8.8X\n",
		    adapter->rcv_unicasts);
	seq_printf(seq, "rx stats: errors                   : %8.8X\n",
		    (u32) adapter->slic_stats.iface.rcv_errors);
	seq_printf(seq, "rx stats: Missed errors            : %8.8X\n",
		    (u32) adapter->slic_stats.iface.rcv_discards);
	seq_printf(seq, "rx stats: drops                    : %8.8X\n",
			(u32) adapter->rcv_drops);
	seq_printf(seq, "tx stats: packets                  : %8.8lX\n",
			adapter->stats.tx_packets);
	seq_printf(seq, "tx stats: bytes                    : %8.8lX\n",
			adapter->stats.tx_bytes);
	seq_printf(seq, "tx stats: errors                   : %8.8X\n",
			(u32) adapter->slic_stats.iface.xmt_errors);
	seq_printf(seq, "rx stats: multicasts               : %8.8lX\n",
			adapter->stats.multicast);
	seq_printf(seq, "tx stats: collision errors         : %8.8X\n",
			(u32) adapter->slic_stats.iface.xmit_collisions);
	seq_printf(seq, "perf: Max rcv frames/isr           : %8.8X\n",
			adapter->max_isr_rcvs);
	seq_printf(seq, "perf: Rcv interrupt yields         : %8.8X\n",
			adapter->rcv_interrupt_yields);
	seq_printf(seq, "perf: Max xmit complete/isr        : %8.8X\n",
			adapter->max_isr_xmits);
	seq_printf(seq, "perf: error interrupts             : %8.8X\n",
			adapter->error_interrupts);
	seq_printf(seq, "perf: error rmiss interrupts       : %8.8X\n",
			adapter->error_rmiss_interrupts);
	seq_printf(seq, "perf: rcv interrupts               : %8.8X\n",
			adapter->rcv_interrupts);
	seq_printf(seq, "perf: xmit interrupts              : %8.8X\n",
			adapter->xmit_interrupts);
	seq_printf(seq, "perf: link event interrupts        : %8.8X\n",
			adapter->linkevent_interrupts);
	seq_printf(seq, "perf: UPR interrupts               : %8.8X\n",
			adapter->upr_interrupts);
	seq_printf(seq, "perf: interrupt count              : %8.8X\n",
			adapter->num_isrs);
	seq_printf(seq, "perf: false interrupts             : %8.8X\n",
			adapter->false_interrupts);
	seq_printf(seq, "perf: All register writes          : %8.8X\n",
			adapter->all_reg_writes);
	seq_printf(seq, "perf: ICR register writes          : %8.8X\n",
			adapter->icr_reg_writes);
	seq_printf(seq, "perf: ISR register writes          : %8.8X\n",
			adapter->isr_reg_writes);
	seq_printf(seq, "ifevents: overflow 802 errors      : %8.8X\n",
			adapter->if_events.oflow802);
	seq_printf(seq, "ifevents: transport overflow errors: %8.8X\n",
			adapter->if_events.Tprtoflow);
	seq_printf(seq, "ifevents: underflow errors         : %8.8X\n",
			adapter->if_events.uflow802);
	seq_printf(seq, "ifevents: receive early            : %8.8X\n",
			adapter->if_events.rcvearly);
	seq_printf(seq, "ifevents: buffer overflows         : %8.8X\n",
			adapter->if_events.Bufov);
	seq_printf(seq, "ifevents: carrier errors           : %8.8X\n",
			adapter->if_events.Carre);
	seq_printf(seq, "ifevents: Long                     : %8.8X\n",
			adapter->if_events.Longe);
	seq_printf(seq, "ifevents: invalid preambles        : %8.8X\n",
			adapter->if_events.Invp);
	seq_printf(seq, "ifevents: CRC errors               : %8.8X\n",
			adapter->if_events.Crc);
	seq_printf(seq, "ifevents: dribble nibbles          : %8.8X\n",
			adapter->if_events.Drbl);
	seq_printf(seq, "ifevents: Code violations          : %8.8X\n",
			adapter->if_events.Code);
	seq_printf(seq, "ifevents: TCP checksum errors      : %8.8X\n",
			adapter->if_events.TpCsum);
	seq_printf(seq, "ifevents: TCP header short errors  : %8.8X\n",
			adapter->if_events.TpHlen);
	seq_printf(seq, "ifevents: IP checksum errors       : %8.8X\n",
			adapter->if_events.IpCsum);
	seq_printf(seq, "ifevents: IP frame incompletes     : %8.8X\n",
			adapter->if_events.IpLen);
	seq_printf(seq, "ifevents: IP headers shorts        : %8.8X\n",
			adapter->if_events.IpHlen);

	return 0;
}