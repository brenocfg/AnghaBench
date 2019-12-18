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
struct TYPE_4__ {int state; int bus_manager_id; int bandwidth_available; int channels_available_hi; int broadcast_channel; int node_ids; void** speed_map; void** topology_map; int /*<<< orphan*/  channels_available_lo; } ;
struct hpsb_host {int node_id; int node_count; int selfid_count; TYPE_2__ csr; int /*<<< orphan*/  is_root; TYPE_1__* driver; scalar_t__ is_irm; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* hw_csr_reg ) (struct hpsb_host*,int,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  be32_add_cpu (void**,int) ; 
 void* cpu_to_be32 (int) ; 
 int csr_crc16 (void**,int) ; 
 int /*<<< orphan*/  stub1 (struct hpsb_host*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void host_reset(struct hpsb_host *host)
{
        host->csr.state &= 0x300;

        host->csr.bus_manager_id = 0x3f;
        host->csr.bandwidth_available = 4915;
	host->csr.channels_available_hi = 0xfffffffe;	/* pre-alloc ch 31 per 1394a-2000 */
        host->csr.channels_available_lo = ~0;
	host->csr.broadcast_channel = 0x80000000 | 31;

	if (host->is_irm) {
		if (host->driver->hw_csr_reg) {
			host->driver->hw_csr_reg(host, 2, 0xfffffffe, ~0);
		}
	}

        host->csr.node_ids = host->node_id << 16;

        if (!host->is_root) {
                /* clear cmstr bit */
                host->csr.state &= ~0x100;
        }

	be32_add_cpu(&host->csr.topology_map[1], 1);
        host->csr.topology_map[2] = cpu_to_be32(host->node_count << 16
                                                | host->selfid_count);
        host->csr.topology_map[0] =
                cpu_to_be32((host->selfid_count + 2) << 16
                            | csr_crc16(host->csr.topology_map + 1,
                                        host->selfid_count + 2));

	be32_add_cpu(&host->csr.speed_map[1], 1);
        host->csr.speed_map[0] = cpu_to_be32(0x3f1 << 16
                                             | csr_crc16(host->csr.speed_map+1,
                                                         0x3f1));
}