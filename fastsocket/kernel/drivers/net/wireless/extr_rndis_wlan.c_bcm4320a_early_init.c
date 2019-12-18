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
struct usbnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RNDIS_BCM4320A ; 
 int /*<<< orphan*/  rndis_copy_module_params (struct usbnet*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm4320a_early_init(struct usbnet *usbdev)
{
	/* copy module parameters for bcm4320a so that iwconfig reports txpower
	 * and workaround parameter is copied to private structure correctly.
	 */
	rndis_copy_module_params(usbdev, RNDIS_BCM4320A);

	/* bcm4320a doesn't handle configuration parameters well. Try
	 * set any and you get partially zeroed mac and broken device.
	 */

	return 0;
}