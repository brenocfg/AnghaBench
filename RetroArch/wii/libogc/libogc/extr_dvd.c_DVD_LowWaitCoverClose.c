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
typedef  int s32 ;
typedef  int /*<<< orphan*/  dvdcallbacklow ;

/* Variables and functions */
 int /*<<< orphan*/  DVD_CVR_MSK ; 
 int /*<<< orphan*/  __dvd_callback ; 
 scalar_t__ __dvd_stopnextint ; 
 int __dvd_waitcoverclose ; 
 int /*<<< orphan*/ * _diReg ; 

s32 DVD_LowWaitCoverClose(dvdcallbacklow cb)
{
	__dvd_callback = cb;
	__dvd_waitcoverclose = 1;
	__dvd_stopnextint = 0;
	_diReg[1] = DVD_CVR_MSK;
	return 1;
}