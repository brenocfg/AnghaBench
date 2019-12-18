#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  data_ref; } ;
struct TYPE_8__ {int /*<<< orphan*/  data_ref; } ;
struct TYPE_7__ {int /*<<< orphan*/  data_ref; } ;
struct TYPE_10__ {TYPE_3__ other; TYPE_2__ user_data_unregistered; TYPE_1__ user_data_registered; } ;
struct TYPE_11__ {int payload_type; TYPE_4__ payload; } ;
typedef  TYPE_5__ H264RawSEIPayload ;

/* Variables and functions */
#define  H264_SEI_TYPE_ALTERNATIVE_TRANSFER 136 
#define  H264_SEI_TYPE_BUFFERING_PERIOD 135 
#define  H264_SEI_TYPE_DISPLAY_ORIENTATION 134 
#define  H264_SEI_TYPE_MASTERING_DISPLAY_COLOUR_VOLUME 133 
#define  H264_SEI_TYPE_PAN_SCAN_RECT 132 
#define  H264_SEI_TYPE_PIC_TIMING 131 
#define  H264_SEI_TYPE_RECOVERY_POINT 130 
#define  H264_SEI_TYPE_USER_DATA_REGISTERED 129 
#define  H264_SEI_TYPE_USER_DATA_UNREGISTERED 128 
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cbs_h264_free_sei_payload(H264RawSEIPayload *payload)
{
    switch (payload->payload_type) {
    case H264_SEI_TYPE_BUFFERING_PERIOD:
    case H264_SEI_TYPE_PIC_TIMING:
    case H264_SEI_TYPE_PAN_SCAN_RECT:
    case H264_SEI_TYPE_RECOVERY_POINT:
    case H264_SEI_TYPE_DISPLAY_ORIENTATION:
    case H264_SEI_TYPE_MASTERING_DISPLAY_COLOUR_VOLUME:
    case H264_SEI_TYPE_ALTERNATIVE_TRANSFER:
        break;
    case H264_SEI_TYPE_USER_DATA_REGISTERED:
        av_buffer_unref(&payload->payload.user_data_registered.data_ref);
        break;
    case H264_SEI_TYPE_USER_DATA_UNREGISTERED:
        av_buffer_unref(&payload->payload.user_data_unregistered.data_ref);
        break;
    default:
        av_buffer_unref(&payload->payload.other.data_ref);
        break;
    }
}