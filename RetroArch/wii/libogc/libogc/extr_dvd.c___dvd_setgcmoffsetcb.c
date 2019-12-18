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
typedef  scalar_t__ s64 ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DVD_LowSetOffset (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __dvd_finaloffsetcb ; 
 int /*<<< orphan*/  __dvd_stategettingerror () ; 
 int /*<<< orphan*/  __dvd_statetimeout () ; 
 int /*<<< orphan*/ * __dvd_usrdata ; 

__attribute__((used)) static void __dvd_setgcmoffsetcb(s32 result)
{
	s64 *pn_data,offset;
	if(result==0x0010) {
		__dvd_statetimeout();
		return;
	}
	if(result==0x0001) {
		pn_data = (s64*)__dvd_usrdata;
		__dvd_usrdata = NULL;

		offset = 0;
		if(pn_data) offset = *pn_data;
		DVD_LowSetOffset(offset,__dvd_finaloffsetcb);
		return;
	}
	__dvd_stategettingerror();
}