#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_1__* par_in; TYPE_2__* priv_data; } ;
struct TYPE_17__ {int flags; scalar_t__ size; scalar_t__ data; } ;
struct TYPE_16__ {scalar_t__ freq; TYPE_3__ pkt; } ;
struct TYPE_15__ {scalar_t__ extradata; scalar_t__ extradata_size; } ;
typedef  TYPE_2__ DumpExtradataContext ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVBSFContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_PKT_FLAG_KEY ; 
 scalar_t__ DUMP_FREQ_ALL ; 
 scalar_t__ DUMP_FREQ_KEYFRAME ; 
 int /*<<< orphan*/  ERANGE ; 
 scalar_t__ INT_MAX ; 
 int av_new_packet (TYPE_3__*,scalar_t__) ; 
 int av_packet_copy_props (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  av_packet_move_ref (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_3__*) ; 
 int ff_bsf_get_packet_ref (TYPE_4__*,TYPE_3__*) ; 
 scalar_t__ memcmp (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int dump_extradata(AVBSFContext *ctx, AVPacket *out)
{
    DumpExtradataContext *s = ctx->priv_data;
    AVPacket *in = &s->pkt;
    int ret = 0;

    ret = ff_bsf_get_packet_ref(ctx, in);
    if (ret < 0)
        return ret;

    if (ctx->par_in->extradata &&
        (s->freq == DUMP_FREQ_ALL ||
         (s->freq == DUMP_FREQ_KEYFRAME && in->flags & AV_PKT_FLAG_KEY)) &&
         in->size >= ctx->par_in->extradata_size &&
         memcmp(in->data, ctx->par_in->extradata, ctx->par_in->extradata_size)) {
        if (in->size >= INT_MAX - ctx->par_in->extradata_size) {
            ret = AVERROR(ERANGE);
            goto fail;
        }

        ret = av_new_packet(out, in->size + ctx->par_in->extradata_size);
        if (ret < 0)
            goto fail;

        ret = av_packet_copy_props(out, in);
        if (ret < 0) {
            av_packet_unref(out);
            goto fail;
        }

        memcpy(out->data, ctx->par_in->extradata, ctx->par_in->extradata_size);
        memcpy(out->data + ctx->par_in->extradata_size, in->data, in->size);
    } else {
        av_packet_move_ref(out, in);
    }

fail:
    av_packet_unref(in);

    return ret;
}