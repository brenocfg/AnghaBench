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
struct hw_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  Wb35Reg_WriteSync (struct hw_data*,int,int) ; 

void Uxx_power_off_procedure(  struct hw_data * pHwData )
{
	// SW, PMU reset and turn off clock
	Wb35Reg_WriteSync( pHwData, 0x03b0, 3 );
	Wb35Reg_WriteSync( pHwData, 0x03f0, 0xf9 );
}