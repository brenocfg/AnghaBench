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
typedef  int uint32_t ;

/* Variables and functions */
 int kProgressMeterEnd ; 
 int vc_progress_meter_end ; 
 int vc_progress_meter_start ; 

__attribute__((used)) static uint32_t vc_progressmeter_range(uint32_t pos)
{
    uint32_t ret;

    if (pos > kProgressMeterEnd) pos = kProgressMeterEnd;
    ret = vc_progress_meter_start 
    	+ ((pos * (vc_progress_meter_end - vc_progress_meter_start)) / kProgressMeterEnd);

    return (ret);
}