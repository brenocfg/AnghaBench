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
 int /*<<< orphan*/  DVD_DISKIDSIZE ; 
 int /*<<< orphan*/  DVD_LowReadId (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __dvd_checkaddonscb ; 
 int /*<<< orphan*/  __dvd_finaladdoncb ; 
 int /*<<< orphan*/  __dvd_tmpid0 ; 
 int /*<<< orphan*/ * _diReg ; 

__attribute__((used)) static void __dvd_checkaddons(dvdcallbacklow cb)
{
	__dvd_finaladdoncb = cb;

	// try to read disc ID.
	_diReg[1] = _diReg[1];
	DCInvalidateRange(&__dvd_tmpid0,DVD_DISKIDSIZE);
	DVD_LowReadId(&__dvd_tmpid0,__dvd_checkaddonscb);
	return;
}