#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  back; int /*<<< orphan*/  size; int /*<<< orphan*/  pool; int /*<<< orphan*/  addr; } ;
union cvmx_buf_ptr {TYPE_1__ s; scalar_t__ u64; } ;
struct TYPE_19__ {int /*<<< orphan*/  tx_dropped; } ;
struct octeon_ethernet {TYPE_7__ stats; scalar_t__ queue; int /*<<< orphan*/  port; } ;
struct net_device {int flags; int /*<<< orphan*/  name; } ;
struct ethhdr {int dummy; } ;
struct TYPE_16__ {scalar_t__ IP_exc; scalar_t__ not_IP; int /*<<< orphan*/  bufs; } ;
struct TYPE_17__ {TYPE_4__ s; } ;
struct TYPE_14__ {int /*<<< orphan*/  back; int /*<<< orphan*/  addr; } ;
struct TYPE_15__ {TYPE_2__ s; } ;
struct TYPE_20__ {TYPE_5__ word2; int /*<<< orphan*/  len; TYPE_3__ packet_ptr; } ;
typedef  TYPE_8__ cvmx_wqe_t ;
struct TYPE_18__ {int n2; int dontfree; int ipoffp1; int /*<<< orphan*/  total_bytes; int /*<<< orphan*/  segs; } ;
struct TYPE_21__ {TYPE_6__ s; scalar_t__ u64; } ;
typedef  TYPE_9__ cvmx_pko_command_word0_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_FPA_PACKET_POOL ; 
 int /*<<< orphan*/  CVMX_FPA_PACKET_POOL_SIZE ; 
 int /*<<< orphan*/  CVMX_FPA_WQE_POOL ; 
 int /*<<< orphan*/  CVMX_PKO_LOCK_CMD_QUEUE ; 
 int CVMX_PKO_QUEUES_PER_PORT_INTERFACE0 ; 
 int CVMX_PKO_QUEUES_PER_PORT_INTERFACE1 ; 
 int /*<<< orphan*/  DEBUGPRINT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DONT_WRITEBACK (int) ; 
 int IFF_UP ; 
 int /*<<< orphan*/  cvm_oct_free_work (TYPE_8__*) ; 
 int /*<<< orphan*/  cvmx_fpa_free (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cvmx_pko_get_num_queues (int /*<<< orphan*/ ) ; 
 int cvmx_pko_send_packet_finish (int /*<<< orphan*/ ,scalar_t__,TYPE_9__,union cvmx_buf_ptr,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_pko_send_packet_prepare (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 struct octeon_ethernet* netdev_priv (struct net_device*) ; 
 scalar_t__ unlikely (int) ; 

int cvm_oct_transmit_qos(struct net_device *dev, void *work_queue_entry,
			 int do_free, int qos)
{
	unsigned long flags;
	union cvmx_buf_ptr hw_buffer;
	cvmx_pko_command_word0_t pko_command;
	int dropped;
	struct octeon_ethernet *priv = netdev_priv(dev);
	cvmx_wqe_t *work = work_queue_entry;

	if (!(dev->flags & IFF_UP)) {
		DEBUGPRINT("%s: Device not up\n", dev->name);
		if (do_free)
			cvm_oct_free_work(work);
		return -1;
	}

	/* The check on CVMX_PKO_QUEUES_PER_PORT_* is designed to completely
	   remove "qos" in the event neither interface supports
	   multiple queues per port */
	if ((CVMX_PKO_QUEUES_PER_PORT_INTERFACE0 > 1) ||
	    (CVMX_PKO_QUEUES_PER_PORT_INTERFACE1 > 1)) {
		if (qos <= 0)
			qos = 0;
		else if (qos >= cvmx_pko_get_num_queues(priv->port))
			qos = 0;
	} else
		qos = 0;

	/* Start off assuming no drop */
	dropped = 0;

	local_irq_save(flags);
	cvmx_pko_send_packet_prepare(priv->port, priv->queue + qos,
				     CVMX_PKO_LOCK_CMD_QUEUE);

	/* Build the PKO buffer pointer */
	hw_buffer.u64 = 0;
	hw_buffer.s.addr = work->packet_ptr.s.addr;
	hw_buffer.s.pool = CVMX_FPA_PACKET_POOL;
	hw_buffer.s.size = CVMX_FPA_PACKET_POOL_SIZE;
	hw_buffer.s.back = work->packet_ptr.s.back;

	/* Build the PKO command */
	pko_command.u64 = 0;
	pko_command.s.n2 = 1;	/* Don't pollute L2 with the outgoing packet */
	pko_command.s.dontfree = !do_free;
	pko_command.s.segs = work->word2.s.bufs;
	pko_command.s.total_bytes = work->len;

	/* Check if we can use the hardware checksumming */
	if (unlikely(work->word2.s.not_IP || work->word2.s.IP_exc))
		pko_command.s.ipoffp1 = 0;
	else
		pko_command.s.ipoffp1 = sizeof(struct ethhdr) + 1;

	/* Send the packet to the output queue */
	if (unlikely
	    (cvmx_pko_send_packet_finish
	     (priv->port, priv->queue + qos, pko_command, hw_buffer,
	      CVMX_PKO_LOCK_CMD_QUEUE))) {
		DEBUGPRINT("%s: Failed to send the packet\n", dev->name);
		dropped = -1;
	}
	local_irq_restore(flags);

	if (unlikely(dropped)) {
		if (do_free)
			cvm_oct_free_work(work);
		priv->stats.tx_dropped++;
	} else if (do_free)
		cvmx_fpa_free(work, CVMX_FPA_WQE_POOL, DONT_WRITEBACK(1));

	return dropped;
}