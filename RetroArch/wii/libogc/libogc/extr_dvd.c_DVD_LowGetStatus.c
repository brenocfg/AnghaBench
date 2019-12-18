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
typedef  int /*<<< orphan*/  dvdcallbacklow ;

/* Variables and functions */
 int /*<<< orphan*/  DVD_LowRequestError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __dvd_finalstatuscb ; 
 int /*<<< orphan*/  __dvd_getstatuscb ; 
 int /*<<< orphan*/ * __dvd_usrdata ; 

s32 DVD_LowGetStatus(u32 *status,dvdcallbacklow cb)
{
	__dvd_finalstatuscb = cb;
	__dvd_usrdata = status;

	DVD_LowRequestError(__dvd_getstatuscb);
	return 1;
}