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
struct wbsoft_priv {int /*<<< orphan*/  sHwData; } ;

/* Variables and functions */
 int /*<<< orphan*/  Mds_Destroy (struct wbsoft_priv*) ; 
 int /*<<< orphan*/  hal_halt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hal_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static void wb35_hw_halt(struct wbsoft_priv *adapter)
{
	Mds_Destroy(adapter);

	/* Turn off Rx and Tx hardware ability */
	hal_stop(&adapter->sHwData);
#ifdef _PE_USB_INI_DUMP_
	printk("[w35und] Hal_stop O.K.\n");
#endif
	/* Waiting Irp completed */
	msleep(100);

	hal_halt(&adapter->sHwData);
}