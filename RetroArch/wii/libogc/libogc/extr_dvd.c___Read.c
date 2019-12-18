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
typedef  int u32 ;
struct timespec {int tv_sec; scalar_t__ tv_nsec; } ;
typedef  int s64 ;
typedef  int /*<<< orphan*/  dvdcallbacklow ;

/* Variables and functions */
 int DVD_DI_DMA ; 
 int DVD_DI_START ; 
 int DVD_READSECTOR ; 
 int /*<<< orphan*/  __SetupTimeoutAlarm (struct timespec*) ; 
 int /*<<< orphan*/  __dvd_callback ; 
 int __dvd_lastcmdwasread ; 
 int __dvd_lastlen ; 
 scalar_t__ __dvd_stopnextint ; 
 int* _diReg ; 

__attribute__((used)) static void __Read(void *buffer,u32 len,s64 offset,dvdcallbacklow cb)
{
	u32 val;
	struct timespec tb;
	__dvd_callback = cb;
	__dvd_stopnextint = 0;
	__dvd_lastcmdwasread = 1;

	_diReg[2] = DVD_READSECTOR;
	_diReg[3] = (u32)(offset>>2);
	_diReg[4] = len;
	_diReg[5] = (u32)buffer;
	_diReg[6] = len;

	__dvd_lastlen = len;

	_diReg[7] = (DVD_DI_DMA|DVD_DI_START);
	val = _diReg[7];
	if(val>0x00a00000) {
		tb.tv_sec = 20;
		tb.tv_nsec = 0;
		__SetupTimeoutAlarm(&tb);
	} else {
		tb.tv_sec = 10;
		tb.tv_nsec = 0;
		__SetupTimeoutAlarm(&tb);
	}
}