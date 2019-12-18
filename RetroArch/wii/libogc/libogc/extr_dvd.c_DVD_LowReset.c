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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  DVD_CVR_MSK ; 
 int /*<<< orphan*/  DVD_DRIVERESET ; 
 int DVD_RESETHARD ; 
 int /*<<< orphan*/  __dvd_drivestate ; 
 int /*<<< orphan*/  __dvd_lastresetend ; 
 int __dvd_resetoccured ; 
 int /*<<< orphan*/ * _diReg ; 
 int* _piReg ; 
 int /*<<< orphan*/  gettime () ; 
 int /*<<< orphan*/  udelay (int) ; 

void DVD_LowReset(u32 reset_mode)
{
	u32 val;

	_diReg[1] = DVD_CVR_MSK;
	val = _piReg[9];
	_piReg[9] = ((val&~0x0004)|0x0001);

	udelay(12);

	if(reset_mode==DVD_RESETHARD) val |= 0x0004;
	val |= 0x0001;
	_piReg[9] = val;

	__dvd_resetoccured = 1;
	__dvd_lastresetend = gettime();
	__dvd_drivestate |= DVD_DRIVERESET;
}