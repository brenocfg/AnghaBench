#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ahc_softc {TYPE_2__* dev_softc; TYPE_1__* platform_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;
struct TYPE_3__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  ahc_linux_isr ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct ahc_softc*) ; 

int
ahc_pci_map_int(struct ahc_softc *ahc)
{
	int error;

	error = request_irq(ahc->dev_softc->irq, ahc_linux_isr,
			    IRQF_SHARED, "aic7xxx", ahc);
	if (error == 0)
		ahc->platform_data->irq = ahc->dev_softc->irq;
	
	return (-error);
}