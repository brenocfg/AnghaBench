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
struct TYPE_4__ {int state; int node_ids; int split_timeout_hi; int split_timeout_lo; int cycle_time; int bus_time; int bus_manager_id; int bandwidth_available; int channels_available_hi; int channels_available_lo; int broadcast_channel; } ;
struct hpsb_host {TYPE_2__ csr; TYPE_1__* driver; } ;
typedef  int quadlet_t ;
struct TYPE_3__ {int (* devctl ) (struct hpsb_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int (* hw_csr_reg ) (struct hpsb_host*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
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
 int /*<<< orphan*/  GET_CYCLE_COUNTER ; 
 int RCODE_ADDRESS_ERROR ; 
 int RCODE_COMPLETE ; 
 int RCODE_TYPE_ERROR ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  out ; 
 int stub1 (struct hpsb_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (struct hpsb_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub3 (struct hpsb_host*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub4 (struct hpsb_host*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub5 (struct hpsb_host*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub6 (struct hpsb_host*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_regs(struct hpsb_host *host, int nodeid, quadlet_t *buf,
                     u64 addr, size_t length, u16 flags)
{
        int csraddr = addr - CSR_REGISTER_BASE;
        int oldcycle;
        quadlet_t ret;

        if ((csraddr | length) & 0x3)
                return RCODE_TYPE_ERROR;

        length /= 4;

        switch (csraddr) {
        case CSR_STATE_CLEAR:
                *(buf++) = cpu_to_be32(host->csr.state);
                out;
        case CSR_STATE_SET:
                *(buf++) = cpu_to_be32(host->csr.state);
                out;
        case CSR_NODE_IDS:
                *(buf++) = cpu_to_be32(host->csr.node_ids);
                out;

        case CSR_RESET_START:
                return RCODE_TYPE_ERROR;

                /* address gap - handled by default below */

        case CSR_SPLIT_TIMEOUT_HI:
                *(buf++) = cpu_to_be32(host->csr.split_timeout_hi);
                out;
        case CSR_SPLIT_TIMEOUT_LO:
                *(buf++) = cpu_to_be32(host->csr.split_timeout_lo);
                out;

                /* address gap */
                return RCODE_ADDRESS_ERROR;

        case CSR_CYCLE_TIME:
                oldcycle = host->csr.cycle_time;
                host->csr.cycle_time =
                        host->driver->devctl(host, GET_CYCLE_COUNTER, 0);

                if (oldcycle > host->csr.cycle_time) {
                        /* cycle time wrapped around */
                        host->csr.bus_time += 1 << 7;
                }
                *(buf++) = cpu_to_be32(host->csr.cycle_time);
                out;
        case CSR_BUS_TIME:
                oldcycle = host->csr.cycle_time;
                host->csr.cycle_time =
                        host->driver->devctl(host, GET_CYCLE_COUNTER, 0);

                if (oldcycle > host->csr.cycle_time) {
                        /* cycle time wrapped around */
                        host->csr.bus_time += (1 << 7);
                }
                *(buf++) = cpu_to_be32(host->csr.bus_time
                                       | (host->csr.cycle_time >> 25));
                out;

                /* address gap */
                return RCODE_ADDRESS_ERROR;

        case CSR_BUSY_TIMEOUT:
                /* not yet implemented */
                return RCODE_ADDRESS_ERROR;

        case CSR_BUS_MANAGER_ID:
                if (host->driver->hw_csr_reg)
                        ret = host->driver->hw_csr_reg(host, 0, 0, 0);
                else
                        ret = host->csr.bus_manager_id;

                *(buf++) = cpu_to_be32(ret);
                out;
        case CSR_BANDWIDTH_AVAILABLE:
                if (host->driver->hw_csr_reg)
                        ret = host->driver->hw_csr_reg(host, 1, 0, 0);
                else
                        ret = host->csr.bandwidth_available;

                *(buf++) = cpu_to_be32(ret);
                out;
        case CSR_CHANNELS_AVAILABLE_HI:
                if (host->driver->hw_csr_reg)
                        ret = host->driver->hw_csr_reg(host, 2, 0, 0);
                else
                        ret = host->csr.channels_available_hi;

                *(buf++) = cpu_to_be32(ret);
                out;
        case CSR_CHANNELS_AVAILABLE_LO:
                if (host->driver->hw_csr_reg)
                        ret = host->driver->hw_csr_reg(host, 3, 0, 0);
                else
                        ret = host->csr.channels_available_lo;

                *(buf++) = cpu_to_be32(ret);
                out;

	case CSR_BROADCAST_CHANNEL:
		*(buf++) = cpu_to_be32(host->csr.broadcast_channel);
		out;

                /* address gap to end - fall through to default */
        default:
                return RCODE_ADDRESS_ERROR;
        }

        return RCODE_COMPLETE;
}