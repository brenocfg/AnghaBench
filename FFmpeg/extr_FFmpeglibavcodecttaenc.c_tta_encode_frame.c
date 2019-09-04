#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int int64_t ;
typedef  int int32_t ;
struct TYPE_26__ {long long channels; int /*<<< orphan*/  sample_fmt; TYPE_4__* priv_data; } ;
struct TYPE_25__ {long long nb_samples; int /*<<< orphan*/  pts; } ;
struct TYPE_24__ {int size; int /*<<< orphan*/  duration; int /*<<< orphan*/  pts; int /*<<< orphan*/  data; } ;
struct TYPE_20__ {int k0; int sum0; int k1; int sum1; } ;
struct TYPE_21__ {int /*<<< orphan*/  round; int /*<<< orphan*/  shift; int /*<<< orphan*/  error; int /*<<< orphan*/  dl; int /*<<< orphan*/  dx; int /*<<< orphan*/  qm; } ;
struct TYPE_23__ {int predictor; TYPE_2__ rice; TYPE_3__ filter; } ;
struct TYPE_19__ {int /*<<< orphan*/  (* filter_process ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_22__ {long long bps; int /*<<< orphan*/  crc_table; TYPE_1__ dsp; TYPE_5__* ch_ctx; } ;
typedef  TYPE_2__ TTARice ;
typedef  TYPE_3__ TTAFilter ;
typedef  TYPE_4__ TTAEncContext ;
typedef  TYPE_5__ TTAChannel ;
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  TYPE_6__ AVPacket ;
typedef  TYPE_7__ AVFrame ;
typedef  TYPE_8__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int INT_MAX ; 
 int UINT32_MAX ; 
 int av_crc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_6__*) ; 
 int ff_alloc_packet2 (TYPE_8__*,TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_samples_to_time_base (TYPE_8__*,int) ; 
 int /*<<< orphan*/ * ff_tta_filter_configs ; 
 int /*<<< orphan*/  ff_tta_filter_init (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_tta_rice_init (TYPE_2__*,int,int) ; 
 int* ff_tta_shift_1 ; 
 int* ff_tta_shift_16 ; 
 int /*<<< orphan*/  flush_put_bits (int /*<<< orphan*/ *) ; 
 int get_sample (TYPE_7__ const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_put_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  put_bits32 (int /*<<< orphan*/ *,int) ; 
 int put_bits_count (int /*<<< orphan*/ *) ; 
 int put_bits_left (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tta_encode_frame(AVCodecContext *avctx, AVPacket *avpkt,
                            const AVFrame *frame, int *got_packet_ptr)
{
    TTAEncContext *s = avctx->priv_data;
    PutBitContext pb;
    int ret, i, out_bytes, cur_chan, res, samples;
    int64_t pkt_size =  frame->nb_samples * 2LL * avctx->channels * s->bps;

pkt_alloc:
    cur_chan = 0, res = 0, samples = 0;
    if ((ret = ff_alloc_packet2(avctx, avpkt, pkt_size, 0)) < 0)
        return ret;
    init_put_bits(&pb, avpkt->data, avpkt->size);

    // init per channel states
    for (i = 0; i < avctx->channels; i++) {
        s->ch_ctx[i].predictor = 0;
        ff_tta_filter_init(&s->ch_ctx[i].filter, ff_tta_filter_configs[s->bps - 1]);
        ff_tta_rice_init(&s->ch_ctx[i].rice, 10, 10);
    }

    for (i = 0; i < frame->nb_samples * avctx->channels; i++) {
        TTAChannel *c = &s->ch_ctx[cur_chan];
        TTAFilter *filter = &c->filter;
        TTARice *rice = &c->rice;
        uint32_t k, unary, outval;
        int32_t value, temp;

        value = get_sample(frame, samples++, avctx->sample_fmt);

        if (avctx->channels > 1) {
            if (cur_chan < avctx->channels - 1)
                value  = res = get_sample(frame, samples, avctx->sample_fmt) - value;
            else
                value -= res / 2;
        }

        temp = value;
#define PRED(x, k) (int32_t)((((uint64_t)(x) << (k)) - (x)) >> (k))
        switch (s->bps) {
        case 1: value -= PRED(c->predictor, 4); break;
        case 2:
        case 3: value -= PRED(c->predictor, 5); break;
        }
        c->predictor = temp;

        s->dsp.filter_process(filter->qm, filter->dx, filter->dl, &filter->error, &value,
                              filter->shift, filter->round);
        outval = (value > 0) ? (value << 1) - 1: -value << 1;

        k = rice->k0;

        rice->sum0 += outval - (rice->sum0 >> 4);
        if (rice->k0 > 0 && rice->sum0 < ff_tta_shift_16[rice->k0])
            rice->k0--;
        else if (rice->sum0 > ff_tta_shift_16[rice->k0 + 1])
            rice->k0++;

        if (outval >= ff_tta_shift_1[k]) {
            outval -= ff_tta_shift_1[k];
            k = rice->k1;

            rice->sum1 += outval - (rice->sum1 >> 4);
            if (rice->k1 > 0 && rice->sum1 < ff_tta_shift_16[rice->k1])
                rice->k1--;
            else if (rice->sum1 > ff_tta_shift_16[rice->k1 + 1])
                rice->k1++;

            unary = 1 + (outval >> k);
            if (unary + 100LL > put_bits_left(&pb)) {
                if (pkt_size < INT_MAX/2) {
                    pkt_size *= 2;
                    av_packet_unref(avpkt);
                    goto pkt_alloc;
                } else
                    return AVERROR(ENOMEM);
            }
            do {
                if (unary > 31) {
                    put_bits(&pb, 31, 0x7FFFFFFF);
                    unary -= 31;
                } else {
                    put_bits(&pb, unary, (1 << unary) - 1);
                    unary = 0;
                }
            } while (unary);
        }

        put_bits(&pb, 1, 0);

        if (k)
            put_bits(&pb, k, outval & (ff_tta_shift_1[k] - 1));

        if (cur_chan < avctx->channels - 1)
            cur_chan++;
        else
            cur_chan = 0;
    }

    flush_put_bits(&pb);
    out_bytes = put_bits_count(&pb) >> 3;
    put_bits32(&pb, av_crc(s->crc_table, UINT32_MAX, avpkt->data, out_bytes) ^ UINT32_MAX);
    flush_put_bits(&pb);

    avpkt->pts      = frame->pts;
    avpkt->size     = out_bytes + 4;
    avpkt->duration = ff_samples_to_time_base(avctx, frame->nb_samples);
    *got_packet_ptr = 1;
    return 0;
}