#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_19__ {TYPE_1__* par_out; TYPE_2__* priv_data; } ;
struct TYPE_18__ {int size; scalar_t__ data; } ;
struct TYPE_17__ {int length_size; int /*<<< orphan*/  extradata_parsed; } ;
struct TYPE_16__ {int extradata_size; int /*<<< orphan*/  extradata; } ;
typedef  TYPE_2__ HEVCBSFContext ;
typedef  int /*<<< orphan*/  GetByteContext ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVBSFContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_WB32 (scalar_t__,int) ; 
 int SIZE_MAX ; 
 int av_grow_packet (TYPE_3__*,int) ; 
 int av_packet_copy_props (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  av_packet_free (TYPE_3__**) ; 
 int /*<<< orphan*/  av_packet_move_ref (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_3__*) ; 
 int /*<<< orphan*/  bytestream2_get_buffer (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int bytestream2_get_byte (int /*<<< orphan*/ *) ; 
 scalar_t__ bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_init (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int bytestream2_peek_byte (int /*<<< orphan*/ *) ; 
 int ff_bsf_get_packet (TYPE_4__*,TYPE_3__**) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hevc_mp4toannexb_filter(AVBSFContext *ctx, AVPacket *out)
{
    HEVCBSFContext *s = ctx->priv_data;
    AVPacket *in;
    GetByteContext gb;

    int got_irap = 0;
    int i, ret = 0;

    ret = ff_bsf_get_packet(ctx, &in);
    if (ret < 0)
        return ret;

    if (!s->extradata_parsed) {
        av_packet_move_ref(out, in);
        av_packet_free(&in);
        return 0;
    }

    bytestream2_init(&gb, in->data, in->size);

    while (bytestream2_get_bytes_left(&gb)) {
        uint32_t nalu_size = 0;
        int      nalu_type;
        int is_irap, add_extradata, extra_size, prev_size;

        for (i = 0; i < s->length_size; i++)
            nalu_size = (nalu_size << 8) | bytestream2_get_byte(&gb);

        nalu_type = (bytestream2_peek_byte(&gb) >> 1) & 0x3f;

        /* prepend extradata to IRAP frames */
        is_irap       = nalu_type >= 16 && nalu_type <= 23;
        add_extradata = is_irap && !got_irap;
        extra_size    = add_extradata * ctx->par_out->extradata_size;
        got_irap     |= is_irap;

        if (SIZE_MAX - nalu_size < 4 ||
            SIZE_MAX - 4 - nalu_size < extra_size) {
            ret = AVERROR_INVALIDDATA;
            goto fail;
        }

        prev_size = out->size;

        ret = av_grow_packet(out, 4 + nalu_size + extra_size);
        if (ret < 0)
            goto fail;

        if (add_extradata)
            memcpy(out->data + prev_size, ctx->par_out->extradata, extra_size);
        AV_WB32(out->data + prev_size + extra_size, 1);
        bytestream2_get_buffer(&gb, out->data + prev_size + 4 + extra_size, nalu_size);
    }

    ret = av_packet_copy_props(out, in);
    if (ret < 0)
        goto fail;

fail:
    if (ret < 0)
        av_packet_unref(out);
    av_packet_free(&in);

    return ret;
}