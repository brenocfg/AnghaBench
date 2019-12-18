#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int s32 ;
typedef  int /*<<< orphan*/  dvdcallbacklow ;
struct TYPE_2__ {int rel_date; } ;

/* Variables and functions */
 int DVD_MODEL04 ; 
 int DVD_MODEL06 ; 
 int DVD_MODEL08 ; 
 int DVD_MODEL08Q ; 
 TYPE_1__ __dvd_driveinfo ; 
 int /*<<< orphan*/  __dvd_finalpatchcb ; 
 int /*<<< orphan*/ * __dvd_patchcode04 ; 
 scalar_t__ __dvd_patchcode04_size ; 
 int /*<<< orphan*/ * __dvd_patchcode06 ; 
 scalar_t__ __dvd_patchcode06_size ; 
 int /*<<< orphan*/ * __dvd_patchcode08 ; 
 scalar_t__ __dvd_patchcode08_size ; 
 int /*<<< orphan*/ * __dvd_patchcodeQ08 ; 
 scalar_t__ __dvd_patchcodeQ08_size ; 
 int /*<<< orphan*/  __dvd_patchdrivecb (int /*<<< orphan*/ ) ; 
 scalar_t__ __dvd_stopnextint ; 
 int /*<<< orphan*/ * __dvdpatchcode ; 
 scalar_t__ __dvdpatchcode_size ; 

s32 DVD_LowPatchDriveCode(dvdcallbacklow cb)
{
	__dvd_finalpatchcb = cb;
	__dvd_stopnextint = 0;

	if(__dvd_driveinfo.rel_date==DVD_MODEL04) {
		__dvdpatchcode = __dvd_patchcode04;
		__dvdpatchcode_size = __dvd_patchcode04_size;
	} else if((__dvd_driveinfo.rel_date&0x0000ff00)==0x00000500) {		// for wii: since i don't know the real date i have to mask & compare.
	} else if(__dvd_driveinfo.rel_date==DVD_MODEL06) {
		__dvdpatchcode = __dvd_patchcode06;
		__dvdpatchcode_size = __dvd_patchcode06_size;
	} else if(__dvd_driveinfo.rel_date==DVD_MODEL08) {
		__dvdpatchcode = __dvd_patchcode08;
		__dvdpatchcode_size = __dvd_patchcode08_size;
	} else if(__dvd_driveinfo.rel_date==DVD_MODEL08Q) {
		__dvdpatchcode = __dvd_patchcodeQ08;
		__dvdpatchcode_size = __dvd_patchcodeQ08_size;
	} else if((__dvd_driveinfo.rel_date&0x0000ff00)==0x00000900) {		// for wii: since i don't know the real date i have to mask & compare.
	} else {
		__dvdpatchcode = NULL;
		__dvdpatchcode_size = 0;
	}

	__dvd_patchdrivecb(0);
	return 1;
}