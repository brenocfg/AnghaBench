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
 int /*<<< orphan*/  CORGI_GPIO_ALL_STROBE_BIT ; 
 int /*<<< orphan*/  CORGI_GPIO_HIGH_SENSE_BIT ; 
 int /*<<< orphan*/  CORGI_GPIO_LOW_SENSE_BIT ; 
 int /*<<< orphan*/  GEDR1 ; 
 int /*<<< orphan*/  GEDR2 ; 
 int /*<<< orphan*/  GPDR2 ; 
 int /*<<< orphan*/  GPSR2 ; 
 int /*<<< orphan*/  KB_DISCHARGE_DELAY ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void corgikbd_activate_all(void)
{
	/* STROBE ALL -> High */
	GPSR2  = CORGI_GPIO_ALL_STROBE_BIT;
	GPDR2 |= CORGI_GPIO_ALL_STROBE_BIT;

	udelay(KB_DISCHARGE_DELAY);

	/* Clear any interrupts we may have triggered when altering the GPIO lines */
	GEDR1 = CORGI_GPIO_HIGH_SENSE_BIT;
	GEDR2 = CORGI_GPIO_LOW_SENSE_BIT;
}