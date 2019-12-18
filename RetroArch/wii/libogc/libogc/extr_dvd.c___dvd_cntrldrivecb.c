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
 int /*<<< orphan*/  DVD_LowSpinMotor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __dvd_finalsudcb ; 
 int /*<<< orphan*/  __dvd_motorcntrl ; 
 int /*<<< orphan*/  __dvd_stategettingerror () ; 
 int /*<<< orphan*/  __dvd_statetimeout () ; 

__attribute__((used)) static void __dvd_cntrldrivecb(s32 result)
{
	if(result==0x0010) {
		__dvd_statetimeout();
		return;
	}
	if(result==0x0001) {
		DVD_LowSpinMotor(__dvd_motorcntrl,__dvd_finalsudcb);
		return;
	}
	__dvd_stategettingerror();
}