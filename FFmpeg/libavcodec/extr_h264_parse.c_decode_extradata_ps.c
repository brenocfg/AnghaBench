#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int type; int /*<<< orphan*/  size_bits; int /*<<< orphan*/  gb; int /*<<< orphan*/  raw_size; int /*<<< orphan*/  raw_data; } ;
struct TYPE_5__ {int nb_nals; TYPE_2__* nals; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  H264ParamSets ;
typedef  TYPE_1__ H2645Packet ;
typedef  TYPE_2__ H2645NAL ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_CODEC_ID_H264 ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
#define  H264_NAL_PPS 129 
#define  H264_NAL_SPS 128 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,...) ; 
 int ff_h2645_packet_split (TYPE_1__*,int /*<<< orphan*/  const*,int,void*,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_h2645_packet_uninit (TYPE_1__*) ; 
 int ff_h264_decode_picture_parameter_set (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ff_h264_decode_seq_parameter_set (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_get_bits8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decode_extradata_ps(const uint8_t *data, int size, H264ParamSets *ps,
                               int is_avc, void *logctx)
{
    H2645Packet pkt = { 0 };
    int i, ret = 0;

    ret = ff_h2645_packet_split(&pkt, data, size, logctx, is_avc, 2, AV_CODEC_ID_H264, 1, 0);
    if (ret < 0) {
        ret = 0;
        goto fail;
    }

    for (i = 0; i < pkt.nb_nals; i++) {
        H2645NAL *nal = &pkt.nals[i];
        switch (nal->type) {
        case H264_NAL_SPS: {
            GetBitContext tmp_gb = nal->gb;
            ret = ff_h264_decode_seq_parameter_set(&tmp_gb, logctx, ps, 0);
            if (ret >= 0)
                break;
            av_log(logctx, AV_LOG_DEBUG,
                   "SPS decoding failure, trying again with the complete NAL\n");
            init_get_bits8(&tmp_gb, nal->raw_data + 1, nal->raw_size - 1);
            ret = ff_h264_decode_seq_parameter_set(&tmp_gb, logctx, ps, 0);
            if (ret >= 0)
                break;
            ret = ff_h264_decode_seq_parameter_set(&nal->gb, logctx, ps, 1);
            if (ret < 0)
                goto fail;
            break;
        }
        case H264_NAL_PPS:
            ret = ff_h264_decode_picture_parameter_set(&nal->gb, logctx, ps,
                                                       nal->size_bits);
            if (ret < 0)
                goto fail;
            break;
        default:
            av_log(logctx, AV_LOG_VERBOSE, "Ignoring NAL type %d in extradata\n",
                   nal->type);
            break;
        }
    }

fail:
    ff_h2645_packet_uninit(&pkt);
    return ret;
}