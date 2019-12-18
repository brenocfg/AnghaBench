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
typedef  int /*<<< orphan*/  dvdcmdblk ;

/* Variables and functions */
 int DVD_DISKIDSIZE ; 
 int /*<<< orphan*/  DVD_ReadDiskID (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void (*) (int,int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/  DVD_SpinUpDriveAsync (int /*<<< orphan*/ *,void (*) (int,int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/  __dvd_diskID ; 
 int /*<<< orphan*/  __dvd_mountusrcb (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __dvd_tmpid0 ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

void callback(s32 result,dvdcmdblk *block)
{
	if(result==0x00) {
		DVD_ReadDiskID(block,&__dvd_tmpid0,callback);
		return;
	}
	else if(result>=DVD_DISKIDSIZE) {
		memcpy(__dvd_diskID,&__dvd_tmpid0,DVD_DISKIDSIZE);
	} else if(result==-4) {
		DVD_SpinUpDriveAsync(block,callback);
		return;
	}
	if(__dvd_mountusrcb) __dvd_mountusrcb(result,block);
}