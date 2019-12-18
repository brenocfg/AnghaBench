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
struct adapter {int flags; int /*<<< orphan*/  tp; } ;

/* Variables and functions */
 int TSO_CAPABLE ; 
 int UDP_CSUM_CAPABLE ; 
 int /*<<< orphan*/  t1_tp_set_ip_checksum_offload (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  t1_tp_set_tcp_checksum_offload (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  t1_tp_set_udp_checksum_offload (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void enable_hw_csum(struct adapter *adapter)
{
	if (adapter->flags & TSO_CAPABLE)
		t1_tp_set_ip_checksum_offload(adapter->tp, 1);	/* for TSO only */
	if (adapter->flags & UDP_CSUM_CAPABLE)
		t1_tp_set_udp_checksum_offload(adapter->tp, 1);
	t1_tp_set_tcp_checksum_offload(adapter->tp, 1);
}