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
struct TYPE_3__ {int busspd; int bustime; } ;
struct TYPE_4__ {TYPE_1__ aic7770_softc; } ;
struct ahc_softc {TYPE_2__ bus_softc; } ;

/* Variables and functions */
 int AUTOFLUSHDIS ; 
 int /*<<< orphan*/  BCTL ; 
 int /*<<< orphan*/  BUSSPD ; 
 int /*<<< orphan*/  BUSTIME ; 
 int ENABLE ; 
 int /*<<< orphan*/  SBLKCTL ; 
 int ahc_chip_init (struct ahc_softc*) ; 
 int ahc_inb (struct ahc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_outb (struct ahc_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
aic7770_chip_init(struct ahc_softc *ahc)
{
	ahc_outb(ahc, BUSSPD, ahc->bus_softc.aic7770_softc.busspd);
	ahc_outb(ahc, BUSTIME, ahc->bus_softc.aic7770_softc.bustime);
	ahc_outb(ahc, SBLKCTL, ahc_inb(ahc, SBLKCTL) & ~AUTOFLUSHDIS);
	ahc_outb(ahc, BCTL, ENABLE);
	return (ahc_chip_init(ahc));
}