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
struct sge_params {int /*<<< orphan*/  large_buf_capacity; } ;
struct sge {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ alloc_rx_resources (struct sge*,struct sge_params*) ; 
 scalar_t__ alloc_tx_resources (struct sge*,struct sge_params*) ; 
 int /*<<< orphan*/  configure_sge (struct sge*,struct sge_params*) ; 
 int /*<<< orphan*/  free_rx_resources (struct sge*) ; 
 int /*<<< orphan*/  jumbo_payload_capacity (struct sge*) ; 

int t1_sge_configure(struct sge *sge, struct sge_params *p)
{
	if (alloc_rx_resources(sge, p))
		return -ENOMEM;
	if (alloc_tx_resources(sge, p)) {
		free_rx_resources(sge);
		return -ENOMEM;
	}
	configure_sge(sge, p);

	/*
	 * Now that we have sized the free lists calculate the payload
	 * capacity of the large buffers.  Other parts of the driver use
	 * this to set the max offload coalescing size so that RX packets
	 * do not overflow our large buffers.
	 */
	p->large_buf_capacity = jumbo_payload_capacity(sge);
	return 0;
}