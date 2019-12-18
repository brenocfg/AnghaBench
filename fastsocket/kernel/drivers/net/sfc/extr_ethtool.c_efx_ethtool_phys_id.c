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
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;
struct efx_nic {TYPE_1__* type; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_id_led ) (struct efx_nic*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_LED_DEFAULT ; 
 int /*<<< orphan*/  EFX_LED_OFF ; 
 int /*<<< orphan*/  EFX_LED_ON ; 
 int HZ ; 
 int /*<<< orphan*/  current ; 
 struct efx_nic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int) ; 
 int /*<<< orphan*/  signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct efx_nic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct efx_nic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct efx_nic*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int efx_ethtool_phys_id(struct net_device *net_dev, u32 count)
{
	struct efx_nic *efx = netdev_priv(net_dev);

	do {
		efx->type->set_id_led(efx, EFX_LED_ON);
		schedule_timeout_interruptible(HZ / 2);

		efx->type->set_id_led(efx, EFX_LED_OFF);
		schedule_timeout_interruptible(HZ / 2);
	} while (!signal_pending(current) && --count != 0);

	efx->type->set_id_led(efx, EFX_LED_DEFAULT);
	return 0;
}