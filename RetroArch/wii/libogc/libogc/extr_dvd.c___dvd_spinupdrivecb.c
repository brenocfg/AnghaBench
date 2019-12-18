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

/* Variables and functions */
 int DVD_CHIPPRESENT ; 
 int DVD_DRIVERESET ; 
 int DVD_INTEROPER ; 
 int /*<<< orphan*/  DVD_RESETHARD ; 
 int /*<<< orphan*/  DVD_Reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __dvd_checkaddons (void (*) (int)) ; 
 int /*<<< orphan*/  __dvd_drivechecked ; 
 int __dvd_drivestate ; 
 int /*<<< orphan*/  __dvd_finalsudcb (int) ; 
 int /*<<< orphan*/  __dvd_fwpatchmem (void (*) (int)) ; 
 int /*<<< orphan*/  __dvd_handlespinup () ; 
 int /*<<< orphan*/  __dvd_stategettingerror () ; 
 int /*<<< orphan*/  __dvd_statetimeout () ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void __dvd_spinupdrivecb(s32 result)
{
	if(result==0x0010) {
		__dvd_statetimeout();
		return;
	}
	if(result==0x0001) {
		if(!__dvd_drivechecked) {
			__dvd_checkaddons(__dvd_spinupdrivecb);
			return;
		}
		if(!(__dvd_drivestate&DVD_CHIPPRESENT)) {
			if(!(__dvd_drivestate&DVD_INTEROPER)) {
				if(!(__dvd_drivestate&DVD_DRIVERESET)) {
					DVD_Reset(DVD_RESETHARD);
					udelay(1150*1000);
				}
				__dvd_fwpatchmem(__dvd_spinupdrivecb);
				return;
			}
			__dvd_handlespinup();
			return;
		}

		__dvd_finalsudcb(result);
		return;
	}
	__dvd_stategettingerror();
}