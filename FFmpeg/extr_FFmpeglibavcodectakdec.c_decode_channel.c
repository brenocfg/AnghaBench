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
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_6__ {scalar_t__ bits_per_raw_sample; } ;
struct TYPE_5__ {int nb_samples; scalar_t__* sample_shift; int* lpc_mode; int nb_subframes; int* subframe_len; int subframe_scale; int /*<<< orphan*/ ** decoded; int /*<<< orphan*/  gb; TYPE_2__* avctx; } ;
typedef  TYPE_1__ TAKDecContext ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int decode_subframe (TYPE_1__*,int /*<<< orphan*/ *,int,int) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_bits_esc4 (int /*<<< orphan*/ *) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_sbits (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int decode_channel(TAKDecContext *s, int chan)
{
    AVCodecContext *avctx = s->avctx;
    GetBitContext *gb     = &s->gb;
    int32_t *decoded      = s->decoded[chan];
    int left              = s->nb_samples - 1;
    int i = 0, ret, prev = 0;

    s->sample_shift[chan] = get_bits_esc4(gb);
    if (s->sample_shift[chan] >= avctx->bits_per_raw_sample)
        return AVERROR_INVALIDDATA;

    *decoded++ = get_sbits(gb, avctx->bits_per_raw_sample - s->sample_shift[chan]);
    s->lpc_mode[chan] = get_bits(gb, 2);
    s->nb_subframes   = get_bits(gb, 3) + 1;

    if (s->nb_subframes > 1) {
        if (get_bits_left(gb) < (s->nb_subframes - 1) * 6)
            return AVERROR_INVALIDDATA;

        for (; i < s->nb_subframes - 1; i++) {
            int v = get_bits(gb, 6);

            s->subframe_len[i] = (v - prev) * s->subframe_scale;
            if (s->subframe_len[i] <= 0)
                return AVERROR_INVALIDDATA;

            left -= s->subframe_len[i];
            prev  = v;
        }

        if (left <= 0)
            return AVERROR_INVALIDDATA;
    }
    s->subframe_len[i] = left;

    prev = 0;
    for (i = 0; i < s->nb_subframes; i++) {
        if ((ret = decode_subframe(s, decoded, s->subframe_len[i], prev)) < 0)
            return ret;
        decoded += s->subframe_len[i];
        prev     = s->subframe_len[i];
    }

    return 0;
}