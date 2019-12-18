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

/* Variables and functions */
 int /*<<< orphan*/  DVD_LowPatchDriveCode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DVD_LowUnlockDrive (void (*) (int)) ; 
 int /*<<< orphan*/  __dvd_finalpatchcb ; 
 int /*<<< orphan*/  __dvd_stategettingerror () ; 
 int /*<<< orphan*/  __dvd_statetimeout () ; 
 int /*<<< orphan*/ * _diReg ; 

__attribute__((used)) static void __dvd_fwpatchcb(s32 result)
{
	static u32 step = 0;
	if(result==0x0010) {
		__dvd_statetimeout();
		return;
	}
	if(result==0x0001) {
		if(step==0x0000) {
			step++;
			_diReg[1] = _diReg[1];
			DVD_LowUnlockDrive(__dvd_fwpatchcb);
			return;
		}
		if(step==0x0001) {
			step = 0;
			DVD_LowPatchDriveCode(__dvd_finalpatchcb);
			return;
		}
	}

	step = 0;
	__dvd_stategettingerror();
}