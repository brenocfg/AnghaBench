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
typedef  int /*<<< orphan*/  LONG_PTR ;
typedef  int /*<<< orphan*/  IMediaEvent ;

/* Variables and functions */
 long EC_COMPLETE ; 
 long EC_DEVICE_LOST ; 
 long EC_ERRORABORT ; 
 scalar_t__ E_ABORT ; 
 int /*<<< orphan*/  IMediaEvent_FreeEventParams (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IMediaEvent_GetEvent (int /*<<< orphan*/ *,long*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dshow_check_event_queue(IMediaEvent *media_event)
{
    LONG_PTR p1, p2;
    long code;
    int ret = 0;

    while (IMediaEvent_GetEvent(media_event, &code, &p1, &p2, 0) != E_ABORT) {
        if (code == EC_COMPLETE || code == EC_DEVICE_LOST || code == EC_ERRORABORT)
            ret = -1;
        IMediaEvent_FreeEventParams(media_event, code, p1, p2);
    }

    return ret;
}