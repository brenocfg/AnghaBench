#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_6__ {int bps; } ;
struct TYPE_7__ {int** decoded; scalar_t__ ch_mode; int blocksize; int /*<<< orphan*/  avctx; int /*<<< orphan*/  gb; TYPE_1__ flac_stream_info; } ;
typedef  TYPE_2__ FLACContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ FLAC_CHMODE_LEFT_SIDE ; 
 scalar_t__ FLAC_CHMODE_MID_SIDE ; 
 scalar_t__ FLAC_CHMODE_RIGHT_SIDE ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  avpriv_report_missing_feature (int /*<<< orphan*/ ,char*) ; 
 int decode_subframe_fixed (TYPE_2__*,int*,int,int) ; 
 int decode_subframe_lpc (TYPE_2__*,int*,int,int) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 void* get_sbits_long (int /*<<< orphan*/ *,int) ; 
 int get_unary (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  show_bits_long (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int decode_subframe(FLACContext *s, int channel)
{
    int32_t *decoded = s->decoded[channel];
    int type, wasted = 0;
    int bps = s->flac_stream_info.bps;
    int i, tmp, ret;

    if (channel == 0) {
        if (s->ch_mode == FLAC_CHMODE_RIGHT_SIDE)
            bps++;
    } else {
        if (s->ch_mode == FLAC_CHMODE_LEFT_SIDE || s->ch_mode == FLAC_CHMODE_MID_SIDE)
            bps++;
    }

    if (get_bits1(&s->gb)) {
        av_log(s->avctx, AV_LOG_ERROR, "invalid subframe padding\n");
        return AVERROR_INVALIDDATA;
    }
    type = get_bits(&s->gb, 6);

    if (get_bits1(&s->gb)) {
        int left = get_bits_left(&s->gb);
        if ( left <= 0 ||
            (left < bps && !show_bits_long(&s->gb, left)) ||
                           !show_bits_long(&s->gb, bps)) {
            av_log(s->avctx, AV_LOG_ERROR,
                   "Invalid number of wasted bits > available bits (%d) - left=%d\n",
                   bps, left);
            return AVERROR_INVALIDDATA;
        }
        wasted = 1 + get_unary(&s->gb, 1, get_bits_left(&s->gb));
        bps -= wasted;
    }
    if (bps > 32) {
        avpriv_report_missing_feature(s->avctx, "Decorrelated bit depth > 32");
        return AVERROR_PATCHWELCOME;
    }

//FIXME use av_log2 for types
    if (type == 0) {
        tmp = get_sbits_long(&s->gb, bps);
        for (i = 0; i < s->blocksize; i++)
            decoded[i] = tmp;
    } else if (type == 1) {
        for (i = 0; i < s->blocksize; i++)
            decoded[i] = get_sbits_long(&s->gb, bps);
    } else if ((type >= 8) && (type <= 12)) {
        if ((ret = decode_subframe_fixed(s, decoded, type & ~0x8, bps)) < 0)
            return ret;
    } else if (type >= 32) {
        if ((ret = decode_subframe_lpc(s, decoded, (type & ~0x20)+1, bps)) < 0)
            return ret;
    } else {
        av_log(s->avctx, AV_LOG_ERROR, "invalid coding type\n");
        return AVERROR_INVALIDDATA;
    }

    if (wasted && wasted < 32) {
        int i;
        for (i = 0; i < s->blocksize; i++)
            decoded[i] = (unsigned)decoded[i] << wasted;
    }

    return 0;
}