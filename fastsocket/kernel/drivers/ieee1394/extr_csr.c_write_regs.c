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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {int node_ids; int split_timeout_hi; int split_timeout_lo; int cycle_time; int bus_time; int broadcast_channel; } ;
struct hpsb_host {int node_id; TYPE_2__ csr; TYPE_1__* driver; } ;
typedef  int /*<<< orphan*/  quadlet_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* devctl ) (struct hpsb_host*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int BUS_MASK ; 
#define  CSR_BANDWIDTH_AVAILABLE 141 
#define  CSR_BROADCAST_CHANNEL 140 
#define  CSR_BUSY_TIMEOUT 139 
#define  CSR_BUS_MANAGER_ID 138 
#define  CSR_BUS_TIME 137 
#define  CSR_CHANNELS_AVAILABLE_HI 136 
#define  CSR_CHANNELS_AVAILABLE_LO 135 
#define  CSR_CYCLE_TIME 134 
#define  CSR_NODE_IDS 133 
 int CSR_REGISTER_BASE ; 
#define  CSR_RESET_START 132 
#define  CSR_SPLIT_TIMEOUT_HI 131 
#define  CSR_SPLIT_TIMEOUT_LO 130 
#define  CSR_STATE_CLEAR 129 
#define  CSR_STATE_SET 128 
 int NODE_MASK ; 
 int RCODE_ADDRESS_ERROR ; 
 int RCODE_COMPLETE ; 
 int RCODE_TYPE_ERROR ; 
 int /*<<< orphan*/  SET_BUS_ID ; 
 int /*<<< orphan*/  SET_CYCLE_COUNTER ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  calculate_expire (TYPE_2__*) ; 
 int /*<<< orphan*/  out ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  stub1 (struct hpsb_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct hpsb_host*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int write_regs(struct hpsb_host *host, int nodeid, int destid,
		      quadlet_t *data, u64 addr, size_t length, u16 flags)
{
        int csraddr = addr - CSR_REGISTER_BASE;

        if ((csraddr | length) & 0x3)
                return RCODE_TYPE_ERROR;

        length /= 4;

        switch (csraddr) {
        case CSR_STATE_CLEAR:
                /* FIXME FIXME FIXME */
                printk("doh, someone wants to mess with state clear\n");
                out;
        case CSR_STATE_SET:
                printk("doh, someone wants to mess with state set\n");
                out;

        case CSR_NODE_IDS:
                host->csr.node_ids &= NODE_MASK << 16;
                host->csr.node_ids |= be32_to_cpu(*(data++)) & (BUS_MASK << 16);
                host->node_id = host->csr.node_ids >> 16;
                host->driver->devctl(host, SET_BUS_ID, host->node_id >> 6);
                out;

        case CSR_RESET_START:
                /* FIXME - perform command reset */
                out;

                /* address gap */
                return RCODE_ADDRESS_ERROR;

        case CSR_SPLIT_TIMEOUT_HI:
                host->csr.split_timeout_hi =
                        be32_to_cpu(*(data++)) & 0x00000007;
		calculate_expire(&host->csr);
                out;
        case CSR_SPLIT_TIMEOUT_LO:
                host->csr.split_timeout_lo =
                        be32_to_cpu(*(data++)) & 0xfff80000;
		calculate_expire(&host->csr);
                out;

                /* address gap */
                return RCODE_ADDRESS_ERROR;

        case CSR_CYCLE_TIME:
                /* should only be set by cycle start packet, automatically */
                host->csr.cycle_time = be32_to_cpu(*data);
                host->driver->devctl(host, SET_CYCLE_COUNTER,
                                       be32_to_cpu(*(data++)));
                out;
        case CSR_BUS_TIME:
                host->csr.bus_time = be32_to_cpu(*(data++)) & 0xffffff80;
                out;

                /* address gap */
                return RCODE_ADDRESS_ERROR;

        case CSR_BUSY_TIMEOUT:
                /* not yet implemented */
                return RCODE_ADDRESS_ERROR;

        case CSR_BUS_MANAGER_ID:
        case CSR_BANDWIDTH_AVAILABLE:
        case CSR_CHANNELS_AVAILABLE_HI:
        case CSR_CHANNELS_AVAILABLE_LO:
                /* these are not writable, only lockable */
                return RCODE_TYPE_ERROR;

	case CSR_BROADCAST_CHANNEL:
		/* only the valid bit can be written */
		host->csr.broadcast_channel = (host->csr.broadcast_channel & ~0x40000000)
                        | (be32_to_cpu(*data) & 0x40000000);
		out;

                /* address gap to end - fall through */
        default:
                return RCODE_ADDRESS_ERROR;
        }

        return RCODE_COMPLETE;
}