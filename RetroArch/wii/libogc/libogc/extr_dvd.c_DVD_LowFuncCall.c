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
typedef  int s32 ;
typedef  int /*<<< orphan*/  dvdcallbacklow ;

/* Variables and functions */
 int DVD_DI_START ; 
 int DVD_FWFUNCCALL ; 
 int /*<<< orphan*/  __dvd_callback ; 
 scalar_t__ __dvd_stopnextint ; 
 int* _diReg ; 

s32 DVD_LowFuncCall(u32 address,dvdcallbacklow cb)
{
	__dvd_callback = cb;
	__dvd_stopnextint = 0;

	_diReg[2] = DVD_FWFUNCCALL;
	_diReg[3] = address;
	_diReg[4] = 0x66756E63;
	_diReg[7] = DVD_DI_START;

	return 1;
}