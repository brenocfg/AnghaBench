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
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  dvdcmdblk ;
typedef  int /*<<< orphan*/  dvdcbcallback ;

/* Variables and functions */
 int /*<<< orphan*/  DVD_RESETHARD ; 
 int /*<<< orphan*/  DVD_Reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DVD_SpinUpDriveAsync (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __dvd_mountusrcb ; 
 int /*<<< orphan*/  callback ; 
 int /*<<< orphan*/  udelay (int) ; 

s32 DVD_MountAsync(dvdcmdblk *block,dvdcbcallback cb)
{
	__dvd_mountusrcb = cb;
	DVD_Reset(DVD_RESETHARD);
	udelay(1150*1000);
	return DVD_SpinUpDriveAsync(block,callback);
}