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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int DVD_BRK_MSK ; 
 int DVD_CHIPPRESENT ; 
 int DVD_DE_MSK ; 
 int DVD_DRIVERESET ; 
 int DVD_INTEROPER ; 
 int /*<<< orphan*/  DVD_LowReset (scalar_t__) ; 
 scalar_t__ DVD_RESETNONE ; 
 int DVD_TC_MSK ; 
 int __dvd_drivestate ; 
 scalar_t__ __dvd_internalretries ; 
 scalar_t__ __dvd_resetrequired ; 
 int* _diReg ; 

void DVD_Reset(u32 reset_mode)
{
	__dvd_drivestate &= ~(DVD_INTEROPER|DVD_CHIPPRESENT|DVD_DRIVERESET);

	if(reset_mode!=DVD_RESETNONE)
		DVD_LowReset(reset_mode);

	_diReg[0] = (DVD_DE_MSK|DVD_TC_MSK|DVD_BRK_MSK);
	_diReg[1] = _diReg[1];

	__dvd_resetrequired = 0;
	__dvd_internalretries = 0;
}