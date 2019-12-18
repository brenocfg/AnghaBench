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
struct efx_rx_queue {int /*<<< orphan*/  rxd; int /*<<< orphan*/  efx; } ;

/* Variables and functions */
 int /*<<< orphan*/  efx_free_special_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void efx_nic_remove_rx(struct efx_rx_queue *rx_queue)
{
	efx_free_special_buffer(rx_queue->efx, &rx_queue->rxd);
}