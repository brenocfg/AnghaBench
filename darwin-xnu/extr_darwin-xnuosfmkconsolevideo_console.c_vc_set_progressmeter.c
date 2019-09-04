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
typedef  int /*<<< orphan*/  spl_t ;

/* Variables and functions */
 int /*<<< orphan*/  internal_set_progressmeter (int) ; 
 scalar_t__ kProgressMeterKernel ; 
 int kProgressMeterMax ; 
 int /*<<< orphan*/  simple_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  splhigh () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_progress_lock ; 
 scalar_t__ vc_progressmeter_enable ; 

void
vc_set_progressmeter(int new_value)
{
    spl_t s;

    s = splhigh();
    simple_lock(&vc_progress_lock);

    if (vc_progressmeter_enable && (kProgressMeterKernel != vc_progressmeter_enable))
    {
	internal_set_progressmeter((new_value * kProgressMeterMax) / 100);
    }

    simple_unlock(&vc_progress_lock);
    splx(s);
}