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
typedef  int /*<<< orphan*/  dvdcallbacklow ;

/* Variables and functions */
 int /*<<< orphan*/  DCInvalidateRange (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DVD_DRVINFSIZE ; 
 int /*<<< orphan*/  DVD_LowInquiry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __dvd_driveinfo ; 
 int /*<<< orphan*/  __dvd_finalpatchcb ; 
 int /*<<< orphan*/  __dvd_fwpatchcb ; 
 int /*<<< orphan*/ * _diReg ; 

__attribute__((used)) static void __dvd_fwpatchmem(dvdcallbacklow cb)
{
	__dvd_finalpatchcb = cb;

	_diReg[1] = _diReg[1];
	DCInvalidateRange(&__dvd_driveinfo,DVD_DRVINFSIZE);
	DVD_LowInquiry(&__dvd_driveinfo,__dvd_fwpatchcb);
	return;
}