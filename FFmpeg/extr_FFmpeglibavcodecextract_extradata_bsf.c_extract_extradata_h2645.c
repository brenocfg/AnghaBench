#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_19__ {int nb_nals; TYPE_2__* nals; } ;
struct TYPE_18__ {TYPE_1__* par_in; TYPE_3__* priv_data; } ;
struct TYPE_17__ {int /*<<< orphan*/ * data; } ;
struct TYPE_16__ {int size; int /*<<< orphan*/ * data; TYPE_5__* buf; } ;
struct TYPE_15__ {scalar_t__ remove; TYPE_7__ h2645_pkt; } ;
struct TYPE_14__ {int const type; scalar_t__ raw_size; int /*<<< orphan*/  raw_data; } ;
struct TYPE_13__ {int /*<<< orphan*/  codec_id; } ;
typedef  TYPE_2__ H2645NAL ;
typedef  TYPE_3__ ExtractExtradataContext ;
typedef  TYPE_4__ AVPacket ;
typedef  TYPE_5__ AVBufferRef ;
typedef  TYPE_6__ AVBSFContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_CODEC_ID_H264 ; 
 int /*<<< orphan*/  AV_CODEC_ID_HEVC ; 
 scalar_t__ AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  AV_WB24 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FF_ARRAY_ELEMS (int const*) ; 
#define  H264_NAL_PPS 132 
#define  H264_NAL_SPS 131 
#define  HEVC_NAL_PPS 130 
#define  HEVC_NAL_SPS 129 
#define  HEVC_NAL_VPS 128 
 TYPE_5__* av_buffer_alloc (scalar_t__) ; 
 int /*<<< orphan*/  av_buffer_unref (TYPE_5__**) ; 
 int /*<<< orphan*/ * av_malloc (scalar_t__) ; 
 int ff_h2645_packet_split (TYPE_7__*,int /*<<< orphan*/ *,int,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ val_in_array (int const*,int,int const) ; 

__attribute__((used)) static int extract_extradata_h2645(AVBSFContext *ctx, AVPacket *pkt,
                                   uint8_t **data, int *size)
{
    static const int extradata_nal_types_hevc[] = {
        HEVC_NAL_VPS, HEVC_NAL_SPS, HEVC_NAL_PPS,
    };
    static const int extradata_nal_types_h264[] = {
        H264_NAL_SPS, H264_NAL_PPS,
    };

    ExtractExtradataContext *s = ctx->priv_data;

    int extradata_size = 0, filtered_size = 0;
    const int *extradata_nal_types;
    int nb_extradata_nal_types;
    int i, has_sps = 0, has_vps = 0, ret = 0;

    if (ctx->par_in->codec_id == AV_CODEC_ID_HEVC) {
        extradata_nal_types    = extradata_nal_types_hevc;
        nb_extradata_nal_types = FF_ARRAY_ELEMS(extradata_nal_types_hevc);
    } else {
        extradata_nal_types    = extradata_nal_types_h264;
        nb_extradata_nal_types = FF_ARRAY_ELEMS(extradata_nal_types_h264);
    }

    ret = ff_h2645_packet_split(&s->h2645_pkt, pkt->data, pkt->size,
                                ctx, 0, 0, ctx->par_in->codec_id, 1, 0);
    if (ret < 0)
        return ret;

    for (i = 0; i < s->h2645_pkt.nb_nals; i++) {
        H2645NAL *nal = &s->h2645_pkt.nals[i];
        if (val_in_array(extradata_nal_types, nb_extradata_nal_types, nal->type)) {
            extradata_size += nal->raw_size + 3;
            if (ctx->par_in->codec_id == AV_CODEC_ID_HEVC) {
                if (nal->type == HEVC_NAL_SPS) has_sps = 1;
                if (nal->type == HEVC_NAL_VPS) has_vps = 1;
            } else {
                if (nal->type == H264_NAL_SPS) has_sps = 1;
            }
        } else if (s->remove) {
            filtered_size += nal->raw_size + 3;
        }
    }

    if (extradata_size &&
        ((ctx->par_in->codec_id == AV_CODEC_ID_HEVC && has_sps && has_vps) ||
         (ctx->par_in->codec_id == AV_CODEC_ID_H264 && has_sps))) {
        AVBufferRef *filtered_buf;
        uint8_t *extradata, *filtered_data;

        if (s->remove) {
            filtered_buf = av_buffer_alloc(filtered_size + AV_INPUT_BUFFER_PADDING_SIZE);
            if (!filtered_buf) {
                return AVERROR(ENOMEM);
            }
            memset(filtered_buf->data + filtered_size, 0, AV_INPUT_BUFFER_PADDING_SIZE);

            filtered_data = filtered_buf->data;
        }

        extradata = av_malloc(extradata_size + AV_INPUT_BUFFER_PADDING_SIZE);
        if (!extradata) {
            av_buffer_unref(&filtered_buf);
            return AVERROR(ENOMEM);
        }
        memset(extradata + extradata_size, 0, AV_INPUT_BUFFER_PADDING_SIZE);

        *data = extradata;
        *size = extradata_size;

        for (i = 0; i < s->h2645_pkt.nb_nals; i++) {
            H2645NAL *nal = &s->h2645_pkt.nals[i];
            if (val_in_array(extradata_nal_types, nb_extradata_nal_types,
                             nal->type)) {
                AV_WB24(extradata, 1); // startcode
                memcpy(extradata + 3, nal->raw_data, nal->raw_size);
                extradata += 3 + nal->raw_size;
            } else if (s->remove) {
                AV_WB24(filtered_data, 1); // startcode
                memcpy(filtered_data + 3, nal->raw_data, nal->raw_size);
                filtered_data += 3 + nal->raw_size;
            }
        }

        if (s->remove) {
            av_buffer_unref(&pkt->buf);
            pkt->buf  = filtered_buf;
            pkt->data = filtered_buf->data;
            pkt->size = filtered_size;
        }
    }

    return 0;
}