#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  (* cb ) (int,TYPE_1__*) ;} ;
typedef  TYPE_1__ dvdcmdblk ;

/* Variables and functions */
 int /*<<< orphan*/  DVD_LowSpinUpDrive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  __dvd_clearwaitingqueue () ; 
 int __dvd_currcmd ; 
 TYPE_1__ __dvd_dummycmdblk ; 
 TYPE_1__* __dvd_executing ; 
 int /*<<< orphan*/  __dvd_extensionsenabled ; 
 int /*<<< orphan*/  __dvd_statecoverclosed_spinupcb ; 
 int /*<<< orphan*/  __dvd_stateready () ; 
 int /*<<< orphan*/  stub1 (int,TYPE_1__*) ; 

void __dvd_statecoverclosed()
{
	dvdcmdblk *blk;
	if(__dvd_currcmd==0x0004 || __dvd_currcmd==0x0005
		|| __dvd_currcmd==0x000d || __dvd_currcmd==0x000f
		|| __dvd_currcmd==0x0010) {
		__dvd_clearwaitingqueue();
		blk = __dvd_executing;
		__dvd_executing = &__dvd_dummycmdblk;
		if(blk->cb) blk->cb(-4,blk);
		__dvd_stateready();
	} else {
		__dvd_extensionsenabled = TRUE;
		DVD_LowSpinUpDrive(__dvd_statecoverclosed_spinupcb);
	}
}