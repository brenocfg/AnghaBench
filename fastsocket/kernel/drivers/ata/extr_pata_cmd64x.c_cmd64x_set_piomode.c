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
struct ata_device {int /*<<< orphan*/  pio_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  cmd64x_set_timing (struct ata_port*,struct ata_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cmd64x_set_piomode(struct ata_port *ap, struct ata_device *adev)
{
	cmd64x_set_timing(ap, adev, adev->pio_mode);
}