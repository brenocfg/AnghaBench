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
 int /*<<< orphan*/  DVD_LowStopMotor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __dvd_stateerrorcb ; 
 int /*<<< orphan*/  __dvd_storeerror (int /*<<< orphan*/ ) ; 

void __dvd_stateerror(s32 result)
{
	__dvd_storeerror(result);
	DVD_LowStopMotor(__dvd_stateerrorcb);
}