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

/* Variables and functions */
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * __dvd_executing ; 
 int __dvd_pauseflag ; 
 int __dvd_pausingflag ; 

void DVD_Pause()
{
	u32 level;

	_CPU_ISR_Disable(level);
	__dvd_pauseflag = 1;
	if(__dvd_executing==NULL) __dvd_pausingflag = 1;
	_CPU_ISR_Restore(level);
}