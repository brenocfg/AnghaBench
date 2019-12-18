#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int offset; int num_frames_to_be_processed; scalar_t__ len; } ;
typedef  TYPE_2__ tBT_SBC_HDR ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ UINT32 ;
struct TYPE_5__ {scalar_t__ rx_flush; } ;
struct TYPE_7__ {int /*<<< orphan*/ * pcmData; int /*<<< orphan*/  context; TYPE_1__ btc_aa_snk_cb; } ;
typedef  int /*<<< orphan*/  OI_UINT32 ;
typedef  int /*<<< orphan*/  OI_STATUS ;
typedef  int /*<<< orphan*/  OI_INT16 ;
typedef  int /*<<< orphan*/  OI_BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*,...) ; 
 int /*<<< orphan*/  APPL_TRACE_ERROR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ AVDT_TSEP_SNK ; 
 int /*<<< orphan*/  OI_CODEC_SBC_DecodeFrame (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OI_SUCCESS (int /*<<< orphan*/ ) ; 
 TYPE_4__ a2dp_sink_local_param ; 
 int /*<<< orphan*/  btc_a2d_data_cb_to_app (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  btc_a2dp_control_get_datachnl_stat () ; 
 scalar_t__ btc_av_get_peer_sep () ; 

__attribute__((used)) static void btc_a2dp_sink_handle_inc_media(tBT_SBC_HDR *p_msg)
{
    UINT8 *sbc_start_frame = ((UINT8 *)(p_msg + 1) + p_msg->offset + 1);
    int count;
    UINT32 pcmBytes, availPcmBytes;
    OI_INT16 *pcmDataPointer = a2dp_sink_local_param.pcmData; /*Will be overwritten on next packet receipt*/
    OI_STATUS status;
    int num_sbc_frames = p_msg->num_frames_to_be_processed;
    UINT32 sbc_frame_len = p_msg->len - 1;
    availPcmBytes = sizeof(a2dp_sink_local_param.pcmData);

    /* XXX: Check if the below check is correct, we are checking for peer to be sink when we are sink */
    if (btc_av_get_peer_sep() == AVDT_TSEP_SNK || (a2dp_sink_local_param.btc_aa_snk_cb.rx_flush)) {
        APPL_TRACE_DEBUG(" State Changed happened in this tick ");
        return;
    }

    // ignore data if no one is listening
    if (!btc_a2dp_control_get_datachnl_stat()) {
        return;
    }

    APPL_TRACE_DEBUG("Number of sbc frames %d, frame_len %d\n", num_sbc_frames, sbc_frame_len);

    for (count = 0; count < num_sbc_frames && sbc_frame_len != 0; count ++) {
        pcmBytes = availPcmBytes;
        status = OI_CODEC_SBC_DecodeFrame(&a2dp_sink_local_param.context, (const OI_BYTE **)&sbc_start_frame,
                                          (OI_UINT32 *)&sbc_frame_len,
                                          (OI_INT16 *)pcmDataPointer,
                                          (OI_UINT32 *)&pcmBytes);
        if (!OI_SUCCESS(status)) {
            APPL_TRACE_ERROR("Decoding failure: %d\n", status);
            break;
        }
        availPcmBytes -= pcmBytes;
        pcmDataPointer += pcmBytes / 2;
        p_msg->offset += (p_msg->len - 1) - sbc_frame_len;
        p_msg->len = sbc_frame_len + 1;
    }

    btc_a2d_data_cb_to_app((uint8_t *)a2dp_sink_local_param.pcmData, (sizeof(a2dp_sink_local_param.pcmData) - availPcmBytes));
}