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
 int /*<<< orphan*/  efx_mdio_write (struct efx_nic*,int,int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void qt2025c_restart_firmware(struct efx_nic *efx)
{
	/* Restart microcontroller execution of firmware from RAM */
	efx_mdio_write(efx, 3, 0xe854, 0x00c0);
	efx_mdio_write(efx, 3, 0xe854, 0x0040);
	msleep(50);
}