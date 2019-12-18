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

/* Variables and functions */
 int /*<<< orphan*/  TXC_REQUIRED_DEVS ; 
 int efx_mdio_links_ok (struct efx_nic*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool txc43128_phy_read_link(struct efx_nic *efx)
{
	return efx_mdio_links_ok(efx, TXC_REQUIRED_DEVS);
}