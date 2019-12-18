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
struct efx_nic {int dummy; } ;
typedef  enum efx_filter_priority { ____Placeholder_efx_filter_priority } efx_filter_priority ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_FILTER_TABLE_RX_IP ; 
 int /*<<< orphan*/  EFX_FILTER_TABLE_RX_MAC ; 
 int /*<<< orphan*/  efx_filter_table_clear (struct efx_nic*,int /*<<< orphan*/ ,int) ; 

void efx_filter_clear_rx(struct efx_nic *efx, enum efx_filter_priority priority)
{
	efx_filter_table_clear(efx, EFX_FILTER_TABLE_RX_IP, priority);
	efx_filter_table_clear(efx, EFX_FILTER_TABLE_RX_MAC, priority);
}