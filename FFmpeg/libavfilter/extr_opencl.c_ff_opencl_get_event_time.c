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
typedef  int /*<<< orphan*/  time_start ;
typedef  int /*<<< orphan*/  time_end ;
typedef  scalar_t__ cl_ulong ;
typedef  int /*<<< orphan*/  cl_event ;

/* Variables and functions */
 int /*<<< orphan*/  CL_PROFILING_COMMAND_END ; 
 int /*<<< orphan*/  CL_PROFILING_COMMAND_START ; 
 int /*<<< orphan*/  clGetEventProfilingInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*,int /*<<< orphan*/ *) ; 

cl_ulong ff_opencl_get_event_time(cl_event event) {
    cl_ulong time_start;
    cl_ulong time_end;

    clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(time_start), &time_start, NULL);
    clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(time_end), &time_end, NULL);

    return time_end - time_start;
}