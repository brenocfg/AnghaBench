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

/* Variables and functions */
 int DVD_GetCmdBlockStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __dvd_dummycmdblk ; 
 int /*<<< orphan*/ * __dvd_executing ; 
 scalar_t__ __dvd_fatalerror ; 
 scalar_t__ __dvd_pausingflag ; 

s32 DVD_GetDriveStatus()
{
	s32 ret;
	u32 level;

	_CPU_ISR_Disable(level);
	if(__dvd_fatalerror) ret = -1;
	else {
		if(__dvd_pausingflag) ret = 8;
		else {
			if(!__dvd_executing || __dvd_executing==&__dvd_dummycmdblk) ret = 0;
			else ret = DVD_GetCmdBlockStatus(__dvd_executing);
		}
	}
	_CPU_ISR_Restore(level);
	return ret;
}