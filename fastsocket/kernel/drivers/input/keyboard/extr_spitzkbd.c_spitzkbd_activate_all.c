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

/* Variables and functions */
 int /*<<< orphan*/  GEDR0 ; 
 int /*<<< orphan*/  GEDR1 ; 
 int /*<<< orphan*/  GEDR2 ; 
 int /*<<< orphan*/  GEDR3 ; 
 int /*<<< orphan*/  GPDR0 ; 
 int /*<<< orphan*/  GPDR1 ; 
 int /*<<< orphan*/  GPDR2 ; 
 int /*<<< orphan*/  GPDR3 ; 
 int /*<<< orphan*/  GPSR0 ; 
 int /*<<< orphan*/  GPSR1 ; 
 int /*<<< orphan*/  GPSR2 ; 
 int /*<<< orphan*/  GPSR3 ; 
 int /*<<< orphan*/  KB_DISCHARGE_DELAY ; 
 int /*<<< orphan*/  SPITZ_GPIO_G0_SENSE_BIT ; 
 int /*<<< orphan*/  SPITZ_GPIO_G0_STROBE_BIT ; 
 int /*<<< orphan*/  SPITZ_GPIO_G1_SENSE_BIT ; 
 int /*<<< orphan*/  SPITZ_GPIO_G1_STROBE_BIT ; 
 int /*<<< orphan*/  SPITZ_GPIO_G2_SENSE_BIT ; 
 int /*<<< orphan*/  SPITZ_GPIO_G2_STROBE_BIT ; 
 int /*<<< orphan*/  SPITZ_GPIO_G3_SENSE_BIT ; 
 int /*<<< orphan*/  SPITZ_GPIO_G3_STROBE_BIT ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void spitzkbd_activate_all(void)
{
	/* STROBE ALL -> High */
	GPSR0  =  SPITZ_GPIO_G0_STROBE_BIT;
	GPDR0 |=  SPITZ_GPIO_G0_STROBE_BIT;
	GPSR1  =  SPITZ_GPIO_G1_STROBE_BIT;
	GPDR1 |=  SPITZ_GPIO_G1_STROBE_BIT;
	GPSR2  =  SPITZ_GPIO_G2_STROBE_BIT;
	GPDR2 |=  SPITZ_GPIO_G2_STROBE_BIT;
	GPSR3  =  SPITZ_GPIO_G3_STROBE_BIT;
	GPDR3 |=  SPITZ_GPIO_G3_STROBE_BIT;

	udelay(KB_DISCHARGE_DELAY);

	/* Clear any interrupts we may have triggered when altering the GPIO lines */
	GEDR0 = SPITZ_GPIO_G0_SENSE_BIT;
	GEDR1 = SPITZ_GPIO_G1_SENSE_BIT;
	GEDR2 = SPITZ_GPIO_G2_SENSE_BIT;
	GEDR3 = SPITZ_GPIO_G3_SENSE_BIT;
}