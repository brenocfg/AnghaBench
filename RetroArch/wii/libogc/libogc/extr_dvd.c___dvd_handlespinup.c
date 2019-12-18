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

/* Variables and functions */
 int /*<<< orphan*/  DVD_LowUnlockDrive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __dvd_handlespinupcb ; 
 int /*<<< orphan*/ * _diReg ; 

__attribute__((used)) static void __dvd_handlespinup()
{
	_diReg[1] = _diReg[1];
	DVD_LowUnlockDrive(__dvd_handlespinupcb);
	return;
}