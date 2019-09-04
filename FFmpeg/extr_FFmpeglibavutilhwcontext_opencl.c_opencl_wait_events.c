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
typedef  scalar_t__ cl_int ;
typedef  int /*<<< orphan*/  cl_event ;
typedef  int /*<<< orphan*/  AVHWFramesContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ CL_SUCCESS ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ clReleaseEvent (int /*<<< orphan*/ ) ; 
 scalar_t__ clWaitForEvents (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int opencl_wait_events(AVHWFramesContext *hwfc,
                              cl_event *events, int nb_events)
{
    cl_int cle;
    int i;

    cle = clWaitForEvents(nb_events, events);
    if (cle != CL_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to wait for event "
               "completion: %d.\n", cle);
        return AVERROR(EIO);
    }

    for (i = 0; i < nb_events; i++) {
        cle = clReleaseEvent(events[i]);
        if (cle != CL_SUCCESS) {
            av_log(hwfc, AV_LOG_ERROR, "Failed to release "
                   "event: %d.\n", cle);
        }
    }

    return 0;
}