#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__* packet_types_received; } ;
typedef  TYPE_1__ PayloadContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,scalar_t__,int) ; 

__attribute__((used)) static void h264_close_context(PayloadContext *data)
{
#ifdef DEBUG
    int ii;

    for (ii = 0; ii < 32; ii++) {
        if (data->packet_types_received[ii])
            av_log(NULL, AV_LOG_DEBUG, "Received %d packets of type %d\n",
                   data->packet_types_received[ii], ii);
    }
#endif
}