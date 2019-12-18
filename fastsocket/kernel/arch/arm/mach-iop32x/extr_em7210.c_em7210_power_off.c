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
 int* IOP3XX_GPOD ; 
 int* IOP3XX_GPOE ; 

void em7210_power_off(void)
{
	*IOP3XX_GPOE &= 0xfe;
	*IOP3XX_GPOD |= 0x01;
}