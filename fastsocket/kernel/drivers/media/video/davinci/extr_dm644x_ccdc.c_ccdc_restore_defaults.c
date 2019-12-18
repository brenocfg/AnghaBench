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
 int CCDC_ALAW ; 
 int CCDC_CULLING ; 
 int /*<<< orphan*/  CCDC_GAMMA_BITS_11_2 ; 
 int /*<<< orphan*/  CCDC_NO_CULLING ; 
 int /*<<< orphan*/  ccdc_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regw (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ccdc_restore_defaults(void)
{
	int i;

	/* disable CCDC */
	ccdc_enable(0);
	/* set all registers to default value */
	for (i = 4; i <= 0x94; i += 4)
		regw(0,  i);
	regw(CCDC_NO_CULLING, CCDC_CULLING);
	regw(CCDC_GAMMA_BITS_11_2, CCDC_ALAW);
}