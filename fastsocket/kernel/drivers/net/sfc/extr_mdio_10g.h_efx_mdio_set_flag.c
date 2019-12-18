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
struct TYPE_2__ {int /*<<< orphan*/  prtad; } ;
struct efx_nic {TYPE_1__ mdio; } ;

/* Variables and functions */
 int /*<<< orphan*/  mdio_set_flag (TYPE_1__*,int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static inline void
efx_mdio_set_flag(struct efx_nic *efx, int devad, int addr,
		  int mask, bool state)
{
	mdio_set_flag(&efx->mdio, efx->mdio.prtad, devad, addr, mask, state);
}