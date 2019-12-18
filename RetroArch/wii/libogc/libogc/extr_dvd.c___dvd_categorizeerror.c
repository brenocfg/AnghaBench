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
typedef  int u32 ;
struct TYPE_2__ {int cmd; } ;

/* Variables and functions */
 int DVD_ERROR (int) ; 
 int DVD_ERROR_MEDIUM_CHANGED ; 
 int DVD_ERROR_MEDIUM_CHANGE_REQ ; 
 int DVD_ERROR_MEDIUM_NOT_PRESENT ; 
 int DVD_ERROR_UNRECOVERABLE_READ ; 
 TYPE_1__* __dvd_executing ; 
 int __dvd_internalretries ; 
 int __dvd_lasterror ; 

__attribute__((used)) static u32 __dvd_categorizeerror(u32 errorcode)
{
	if((errorcode-0x20000)==0x0400) {
		__dvd_lasterror = errorcode;
		return 1;
	}

	if(DVD_ERROR(errorcode)==DVD_ERROR_MEDIUM_CHANGED
		|| DVD_ERROR(errorcode)==DVD_ERROR_MEDIUM_NOT_PRESENT
		|| DVD_ERROR(errorcode)==DVD_ERROR_MEDIUM_CHANGE_REQ
		|| (DVD_ERROR(errorcode)-0x40000)==0x3100) return 0;

	__dvd_internalretries++;
	if(__dvd_internalretries==2) {
		if(__dvd_lasterror==DVD_ERROR(errorcode)) {
			__dvd_lasterror = DVD_ERROR(errorcode);
			return 1;
		}
		__dvd_lasterror = DVD_ERROR(errorcode);
		return 2;
	}

	__dvd_lasterror = DVD_ERROR(errorcode);
	if(DVD_ERROR(errorcode)!=DVD_ERROR_UNRECOVERABLE_READ) {
		if(__dvd_executing->cmd!=0x0005) return 3;
	}
	return 2;
}