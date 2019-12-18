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
typedef  int /*<<< orphan*/  s64 ;
typedef  int s32 ;
typedef  int /*<<< orphan*/  dvdcallbacklow ;

/* Variables and functions */
 int /*<<< orphan*/  DVD_LowUnlockDrive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __dvd_finaloffsetcb ; 
 int /*<<< orphan*/  __dvd_setgcmoffsetcb ; 
 scalar_t__ __dvd_stopnextint ; 
 int /*<<< orphan*/ * __dvd_usrdata ; 

s32 DVD_LowSetGCMOffset(s64 offset,dvdcallbacklow cb)
{
	static s64 loc_offset = 0;
	loc_offset = offset;

	__dvd_finaloffsetcb = cb;
	__dvd_stopnextint = 0;
	__dvd_usrdata = &loc_offset;

	DVD_LowUnlockDrive(__dvd_setgcmoffsetcb);
	return 1;
}