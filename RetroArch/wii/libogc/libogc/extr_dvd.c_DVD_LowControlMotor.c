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
typedef  int /*<<< orphan*/  u32 ;
typedef  int s32 ;
typedef  int /*<<< orphan*/  dvdcallbacklow ;

/* Variables and functions */
 int /*<<< orphan*/  DVD_LowUnlockDrive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __dvd_cntrldrivecb ; 
 int /*<<< orphan*/  __dvd_finalsudcb ; 
 int /*<<< orphan*/  __dvd_motorcntrl ; 
 scalar_t__ __dvd_stopnextint ; 

s32 DVD_LowControlMotor(u32 mode,dvdcallbacklow cb)
{
	__dvd_stopnextint = 0;
	__dvd_motorcntrl = mode;
	__dvd_finalsudcb = cb;
	DVD_LowUnlockDrive(__dvd_cntrldrivecb);

	return 1;

}