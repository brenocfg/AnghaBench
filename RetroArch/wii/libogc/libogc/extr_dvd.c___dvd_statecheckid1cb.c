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

/* Variables and functions */
 int /*<<< orphan*/  DVD_DISKIDSIZE ; 
 int /*<<< orphan*/  LWP_ThreadBroadcast (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __dvd_diskID ; 
 int __dvd_ready ; 
 int /*<<< orphan*/  __dvd_tmpid0 ; 
 int /*<<< orphan*/  __dvd_wait_queue ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __dvd_statecheckid1cb(s32 result)
{
	__dvd_ready = 1;
	if(memcmp(__dvd_diskID,&__dvd_tmpid0,DVD_DISKIDSIZE)) memcpy(__dvd_diskID,&__dvd_tmpid0,DVD_DISKIDSIZE);
	LWP_ThreadBroadcast(__dvd_wait_queue);
}