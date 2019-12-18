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
struct net_device_stats {void* tx_bytes; void* rx_bytes; void* tx_packets; void* rx_packets; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct net_device_stats*,int /*<<< orphan*/ ,int) ; 
 void* pm3386_get_stat (int,int) ; 
 int pm3386_port_reg_read (int,int,int) ; 
 int /*<<< orphan*/  pm3386_port_reg_write (int,int,int,int) ; 

void pm3386_get_stats(int port, struct net_device_stats *stats)
{
	/*
	 * Snapshot statistics counters.
	 */
	pm3386_port_reg_write(port, 0x500, 0x100, 0x0001);
	while (pm3386_port_reg_read(port, 0x500, 0x100) & 0x0001)
		;

	memset(stats, 0, sizeof(*stats));

	stats->rx_packets = pm3386_get_stat(port, 0x510);
	stats->tx_packets = pm3386_get_stat(port, 0x590);
	stats->rx_bytes = pm3386_get_stat(port, 0x514);
	stats->tx_bytes = pm3386_get_stat(port, 0x594);
	/* @@@ Add other stats.  */
}