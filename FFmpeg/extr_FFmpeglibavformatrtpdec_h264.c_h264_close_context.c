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
typedef  int /*<<< orphan*/  PayloadContext ;

/* Variables and functions */

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