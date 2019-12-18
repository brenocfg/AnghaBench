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
typedef  TYPE_5__ H265RawSEIPayload ;

/* Variables and functions */
#define  HEVC_SEI_TYPE_ACTIVE_PARAMETER_SETS 141 
#define  HEVC_SEI_TYPE_ALPHA_CHANNEL_INFO 140 
#define  HEVC_SEI_TYPE_ALTERNATIVE_TRANSFER_CHARACTERISTICS 139 
#define  HEVC_SEI_TYPE_BUFFERING_PERIOD 138 
#define  HEVC_SEI_TYPE_CONTENT_LIGHT_LEVEL_INFO 137 
#define  HEVC_SEI_TYPE_DECODED_PICTURE_HASH 136 
#define  HEVC_SEI_TYPE_DISPLAY_ORIENTATION 135 
#define  HEVC_SEI_TYPE_MASTERING_DISPLAY_INFO 134 
#define  HEVC_SEI_TYPE_PAN_SCAN_RECT 133 
#define  HEVC_SEI_TYPE_PICTURE_TIMING 132 
#define  HEVC_SEI_TYPE_RECOVERY_POINT 131 
#define  HEVC_SEI_TYPE_TIME_CODE 130 
#define  HEVC_SEI_TYPE_USER_DATA_REGISTERED_ITU_T_T35 129 
#define  HEVC_SEI_TYPE_USER_DATA_UNREGISTERED 128 
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cbs_h265_free_sei_payload(H265RawSEIPayload *payload)
{
    switch (payload->payload_type) {
    case HEVC_SEI_TYPE_BUFFERING_PERIOD:
    case HEVC_SEI_TYPE_PICTURE_TIMING:
    case HEVC_SEI_TYPE_PAN_SCAN_RECT:
    case HEVC_SEI_TYPE_RECOVERY_POINT:
    case HEVC_SEI_TYPE_DISPLAY_ORIENTATION:
    case HEVC_SEI_TYPE_ACTIVE_PARAMETER_SETS:
    case HEVC_SEI_TYPE_DECODED_PICTURE_HASH:
    case HEVC_SEI_TYPE_TIME_CODE:
    case HEVC_SEI_TYPE_MASTERING_DISPLAY_INFO:
    case HEVC_SEI_TYPE_CONTENT_LIGHT_LEVEL_INFO:
    case HEVC_SEI_TYPE_ALTERNATIVE_TRANSFER_CHARACTERISTICS:
    case HEVC_SEI_TYPE_ALPHA_CHANNEL_INFO:
        break;
    case HEVC_SEI_TYPE_USER_DATA_REGISTERED_ITU_T_T35:
        av_buffer_unref(&payload->payload.user_data_registered.data_ref);
        break;
    case HEVC_SEI_TYPE_USER_DATA_UNREGISTERED:
        av_buffer_unref(&payload->payload.user_data_unregistered.data_ref);
        break;
    default:
        av_buffer_unref(&payload->payload.other.data_ref);
        break;
    }
}