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
struct efx_rx_queue {unsigned int notified_count; unsigned int added_count; int ptr_mask; struct efx_nic* efx; } ;
struct efx_nic {int dummy; } ;
typedef  int /*<<< orphan*/  efx_dword_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_POPULATE_DWORD_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  FRF_AZ_RX_DESC_WPTR_DWORD ; 
 int /*<<< orphan*/  FR_AZ_RX_DESC_UPD_DWORD_P0 ; 
 int /*<<< orphan*/  efx_build_rx_desc (struct efx_rx_queue*,int) ; 
 int /*<<< orphan*/  efx_rx_queue_index (struct efx_rx_queue*) ; 
 int /*<<< orphan*/  efx_writed_page (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

void efx_nic_notify_rx_desc(struct efx_rx_queue *rx_queue)
{
	struct efx_nic *efx = rx_queue->efx;
	efx_dword_t reg;
	unsigned write_ptr;

	while (rx_queue->notified_count != rx_queue->added_count) {
		efx_build_rx_desc(
			rx_queue,
			rx_queue->notified_count & rx_queue->ptr_mask);
		++rx_queue->notified_count;
	}

	wmb();
	write_ptr = rx_queue->added_count & rx_queue->ptr_mask;
	EFX_POPULATE_DWORD_1(reg, FRF_AZ_RX_DESC_WPTR_DWORD, write_ptr);
	efx_writed_page(efx, &reg, FR_AZ_RX_DESC_UPD_DWORD_P0,
			efx_rx_queue_index(rx_queue));
}