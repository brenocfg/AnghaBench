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
struct ata_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_pata_set_dmamode (struct ata_port*,struct ata_device*,int) ; 

__attribute__((used)) static void ich_set_dmamode(struct ata_port *ap, struct ata_device *adev)
{
	do_pata_set_dmamode(ap, adev, 1);
}