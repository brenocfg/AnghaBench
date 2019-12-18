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

/* Variables and functions */
 int /*<<< orphan*/  LWP_ThreadBroadcast (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __dvd_wait_queue ; 

__attribute__((used)) static void __dvd_spinupdrivesynccb(s32 result,dvdcmdblk *block)
{
	LWP_ThreadBroadcast(__dvd_wait_queue);
}