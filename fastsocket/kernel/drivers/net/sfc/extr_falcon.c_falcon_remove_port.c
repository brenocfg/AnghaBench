#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct efx_nic {int /*<<< orphan*/  stats_buffer; TYPE_1__* phy_op; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* remove ) (struct efx_nic*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  efx_nic_free_buffer (struct efx_nic*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct efx_nic*) ; 

__attribute__((used)) static void falcon_remove_port(struct efx_nic *efx)
{
	efx->phy_op->remove(efx);
	efx_nic_free_buffer(efx, &efx->stats_buffer);
}