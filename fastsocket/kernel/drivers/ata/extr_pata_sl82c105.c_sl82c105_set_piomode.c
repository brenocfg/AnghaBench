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
struct ata_port {int dummy; } ;
struct ata_device {scalar_t__ pio_mode; } ;

/* Variables and functions */
 scalar_t__ XFER_PIO_0 ; 
 int /*<<< orphan*/  sl82c105_configure_piomode (struct ata_port*,struct ata_device*,scalar_t__) ; 

__attribute__((used)) static void sl82c105_set_piomode(struct ata_port *ap, struct ata_device *adev)
{
	sl82c105_configure_piomode(ap, adev, adev->pio_mode - XFER_PIO_0);
}