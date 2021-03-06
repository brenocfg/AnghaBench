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
struct timespec {int tv_sec; scalar_t__ tv_nsec; } ;
typedef  int s32 ;
typedef  int /*<<< orphan*/  dvdcallbacklow ;

/* Variables and functions */
 int /*<<< orphan*/  DVD_DI_START ; 
 int /*<<< orphan*/  DVD_REQUESTERROR ; 
 int /*<<< orphan*/  __SetupTimeoutAlarm (struct timespec*) ; 
 int /*<<< orphan*/  __dvd_callback ; 
 scalar_t__ __dvd_stopnextint ; 
 int /*<<< orphan*/ * _diReg ; 

s32 DVD_LowRequestError(dvdcallbacklow cb)
{
	struct timespec tb;

	__dvd_callback = cb;
	__dvd_stopnextint = 0;

	_diReg[2] = DVD_REQUESTERROR;
	_diReg[7] = DVD_DI_START;

	tb.tv_sec = 10;
	tb.tv_nsec = 0;
	__SetupTimeoutAlarm(&tb);

	return 1;
}