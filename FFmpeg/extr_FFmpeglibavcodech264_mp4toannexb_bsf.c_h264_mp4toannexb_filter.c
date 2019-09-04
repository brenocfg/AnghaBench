#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int int32_t ;
struct TYPE_20__ {TYPE_1__* par_out; TYPE_2__* priv_data; } ;
struct TYPE_19__ {int* data; int size; } ;
struct TYPE_18__ {int length_size; int idr_sps_seen; int new_idr; int idr_pps_seen; int sps_offset; int pps_offset; int /*<<< orphan*/  extradata_parsed; } ;
struct TYPE_17__ {int extradata_size; int /*<<< orphan*/ * extradata; } ;
typedef  TYPE_2__ H264BSFContext ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVBSFContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  EINVAL ; 
 int H264_NAL_IDR_SLICE ; 
 int H264_NAL_PPS ; 
 int H264_NAL_SLICE ; 
 int H264_NAL_SPS ; 
 int alloc_and_copy (TYPE_3__*,int /*<<< orphan*/ *,int,int const*,int,int) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int av_packet_copy_props (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  av_packet_free (TYPE_3__**) ; 
 int /*<<< orphan*/  av_packet_move_ref (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_3__*) ; 
 int ff_bsf_get_packet (TYPE_4__*,TYPE_3__**) ; 

__attribute__((used)) static int h264_mp4toannexb_filter(AVBSFContext *ctx, AVPacket *out)
{
    H264BSFContext *s = ctx->priv_data;

    AVPacket *in;
    uint8_t unit_type;
    int32_t nal_size;
    uint32_t cumul_size    = 0;
    const uint8_t *buf;
    const uint8_t *buf_end;
    int            buf_size;
    int ret = 0, i;

    ret = ff_bsf_get_packet(ctx, &in);
    if (ret < 0)
        return ret;

    /* nothing to filter */
    if (!s->extradata_parsed) {
        av_packet_move_ref(out, in);
        av_packet_free(&in);
        return 0;
    }

    buf      = in->data;
    buf_size = in->size;
    buf_end  = in->data + in->size;

    do {
        ret= AVERROR(EINVAL);
        if (buf + s->length_size > buf_end)
            goto fail;

        for (nal_size = 0, i = 0; i<s->length_size; i++)
            nal_size = (nal_size << 8) | buf[i];

        buf += s->length_size;
        unit_type = *buf & 0x1f;

        if (nal_size > buf_end - buf || nal_size < 0)
            goto fail;

        if (unit_type == H264_NAL_SPS)
            s->idr_sps_seen = s->new_idr = 1;
        else if (unit_type == H264_NAL_PPS) {
            s->idr_pps_seen = s->new_idr = 1;
            /* if SPS has not been seen yet, prepend the AVCC one to PPS */
            if (!s->idr_sps_seen) {
                if (s->sps_offset == -1)
                    av_log(ctx, AV_LOG_WARNING, "SPS not present in the stream, nor in AVCC, stream may be unreadable\n");
                else {
                    if ((ret = alloc_and_copy(out,
                                         ctx->par_out->extradata + s->sps_offset,
                                         s->pps_offset != -1 ? s->pps_offset : ctx->par_out->extradata_size - s->sps_offset,
                                         buf, nal_size, 1)) < 0)
                        goto fail;
                    s->idr_sps_seen = 1;
                    goto next_nal;
                }
            }
        }

        /* if this is a new IDR picture following an IDR picture, reset the idr flag.
         * Just check first_mb_in_slice to be 0 as this is the simplest solution.
         * This could be checking idr_pic_id instead, but would complexify the parsing. */
        if (!s->new_idr && unit_type == H264_NAL_IDR_SLICE && (buf[1] & 0x80))
            s->new_idr = 1;

        /* prepend only to the first type 5 NAL unit of an IDR picture, if no sps/pps are already present */
        if (s->new_idr && unit_type == H264_NAL_IDR_SLICE && !s->idr_sps_seen && !s->idr_pps_seen) {
            if ((ret=alloc_and_copy(out,
                               ctx->par_out->extradata, ctx->par_out->extradata_size,
                               buf, nal_size, 1)) < 0)
                goto fail;
            s->new_idr = 0;
        /* if only SPS has been seen, also insert PPS */
        } else if (s->new_idr && unit_type == H264_NAL_IDR_SLICE && s->idr_sps_seen && !s->idr_pps_seen) {
            if (s->pps_offset == -1) {
                av_log(ctx, AV_LOG_WARNING, "PPS not present in the stream, nor in AVCC, stream may be unreadable\n");
                if ((ret = alloc_and_copy(out, NULL, 0, buf, nal_size, 0)) < 0)
                    goto fail;
            } else if ((ret = alloc_and_copy(out,
                                        ctx->par_out->extradata + s->pps_offset, ctx->par_out->extradata_size - s->pps_offset,
                                        buf, nal_size, 1)) < 0)
                goto fail;
        } else {
            if ((ret=alloc_and_copy(out, NULL, 0, buf, nal_size, unit_type == H264_NAL_SPS || unit_type == H264_NAL_PPS)) < 0)
                goto fail;
            if (!s->new_idr && unit_type == H264_NAL_SLICE) {
                s->new_idr = 1;
                s->idr_sps_seen = 0;
                s->idr_pps_seen = 0;
            }
        }

next_nal:
        buf        += nal_size;
        cumul_size += nal_size + s->length_size;
    } while (cumul_size < buf_size);

    ret = av_packet_copy_props(out, in);
    if (ret < 0)
        goto fail;

fail:
    if (ret < 0)
        av_packet_unref(out);
    av_packet_free(&in);

    return ret;
}