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
 int BIT (int) ; 
 int dm6444evm_msp430_get_pins () ; 

__attribute__((used)) static int dm6444evm_mmc_get_ro(int module)
{
	int status = dm6444evm_msp430_get_pins();

	return (status < 0) ? status : status & BIT(6 + 8);
}