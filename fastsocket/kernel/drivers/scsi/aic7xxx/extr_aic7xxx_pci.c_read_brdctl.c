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
typedef  int uint8_t ;
struct ahc_softc {int chip; char channel; int features; } ;

/* Variables and functions */
 int AHC_AIC7895 ; 
 int AHC_CHIPID_MASK ; 
 int AHC_ULTRA2 ; 
 int BRDCS ; 
 int /*<<< orphan*/  BRDCTL ; 
 int BRDRW ; 
 int BRDRW_ULTRA2 ; 
 int /*<<< orphan*/  ahc_flush_device_writes (struct ahc_softc*) ; 
 int ahc_inb (struct ahc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_outb (struct ahc_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint8_t
read_brdctl(struct ahc_softc *ahc)
{
	uint8_t brdctl;
	uint8_t value;

	if ((ahc->chip & AHC_CHIPID_MASK) == AHC_AIC7895) {
		brdctl = BRDRW;
	 	if (ahc->channel == 'B')
			brdctl |= BRDCS;
	} else if ((ahc->features & AHC_ULTRA2) != 0) {
		brdctl = BRDRW_ULTRA2;
	} else {
		brdctl = BRDRW|BRDCS;
	}
	ahc_outb(ahc, BRDCTL, brdctl);
	ahc_flush_device_writes(ahc);
	value = ahc_inb(ahc, BRDCTL);
	ahc_outb(ahc, BRDCTL, 0);
	return (value);
}