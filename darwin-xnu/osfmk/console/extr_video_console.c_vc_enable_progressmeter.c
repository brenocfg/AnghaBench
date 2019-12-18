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
 int /*<<< orphan*/  internal_enable_progressmeter (int /*<<< orphan*/ ) ; 
 scalar_t__ kProgressMeterKernel ; 
 int /*<<< orphan*/  kProgressMeterOff ; 
 int /*<<< orphan*/  kProgressMeterUser ; 
 scalar_t__ vc_progressmeter_enable ; 
 int vc_progressmeter_hold ; 

void
vc_enable_progressmeter(int new_value)
{
    if (kProgressMeterKernel == vc_progressmeter_enable)
    {
    	vc_progressmeter_hold = new_value;
    }
    else
    {
	internal_enable_progressmeter(new_value ? kProgressMeterUser : kProgressMeterOff);
    }
}