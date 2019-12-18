#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mlx4_counter {int /*<<< orphan*/  rx_frames; int /*<<< orphan*/  tx_frames; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  tx_bytes; } ;
struct ib_pma_portcounters {void* port_rcv_packets; void* port_xmit_packets; void* port_rcv_data; void* port_xmit_data; } ;

/* Variables and functions */
 int be64_to_cpu (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int) ; 

__attribute__((used)) static void edit_counter(struct mlx4_counter *cnt,
					struct ib_pma_portcounters *pma_cnt)
{
	pma_cnt->port_xmit_data = cpu_to_be32((be64_to_cpu(cnt->tx_bytes)>>2));
	pma_cnt->port_rcv_data  = cpu_to_be32((be64_to_cpu(cnt->rx_bytes)>>2));
	pma_cnt->port_xmit_packets = cpu_to_be32(be64_to_cpu(cnt->tx_frames));
	pma_cnt->port_rcv_packets  = cpu_to_be32(be64_to_cpu(cnt->rx_frames));
}