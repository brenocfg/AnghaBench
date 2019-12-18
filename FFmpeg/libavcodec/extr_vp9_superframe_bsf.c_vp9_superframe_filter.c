#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int n_cache; TYPE_2__** cache; } ;
typedef  TYPE_1__ VP9BSFContext ;
struct TYPE_18__ {TYPE_1__* priv_data; } ;
struct TYPE_17__ {int* data; int size; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVBSFContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  ENOSYS ; 
 int MAX_CACHE ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int av_packet_copy_props (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  av_packet_move_ref (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_2__*) ; 
 int ff_bsf_get_packet_ref (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int init_get_bits8 (int /*<<< orphan*/ *,int*,int) ; 
 int merge_superframe (TYPE_2__**,int,TYPE_2__*) ; 

__attribute__((used)) static int vp9_superframe_filter(AVBSFContext *ctx, AVPacket *pkt)
{
    GetBitContext gb;
    VP9BSFContext *s = ctx->priv_data;
    int res, invisible, profile, marker, uses_superframe_syntax = 0, n;

    res = ff_bsf_get_packet_ref(ctx, pkt);
    if (res < 0)
        return res;

    marker = pkt->data[pkt->size - 1];
    if ((marker & 0xe0) == 0xc0) {
        int nbytes = 1 + ((marker >> 3) & 0x3);
        int n_frames = 1 + (marker & 0x7), idx_sz = 2 + n_frames * nbytes;

        uses_superframe_syntax = pkt->size >= idx_sz && pkt->data[pkt->size - idx_sz] == marker;
    }

    if ((res = init_get_bits8(&gb, pkt->data, pkt->size)) < 0)
        goto done;

    get_bits(&gb, 2); // frame marker
    profile  = get_bits1(&gb);
    profile |= get_bits1(&gb) << 1;
    if (profile == 3) profile += get_bits1(&gb);

    if (get_bits1(&gb)) {
        invisible = 0;
    } else {
        get_bits1(&gb); // keyframe
        invisible = !get_bits1(&gb);
    }

    if (uses_superframe_syntax && s->n_cache > 0) {
        av_log(ctx, AV_LOG_ERROR,
               "Mixing of superframe syntax and naked VP9 frames not supported\n");
        res = AVERROR(ENOSYS);
        goto done;
    } else if ((!invisible || uses_superframe_syntax) && !s->n_cache) {
        // passthrough
        return 0;
    } else if (s->n_cache + 1 >= MAX_CACHE) {
        av_log(ctx, AV_LOG_ERROR,
               "Too many invisible frames\n");
        res = AVERROR_INVALIDDATA;
        goto done;
    }

    av_packet_move_ref(s->cache[s->n_cache++], pkt);

    if (invisible) {
        return AVERROR(EAGAIN);
    }
    av_assert0(s->n_cache > 0);

    // build superframe
    if ((res = merge_superframe(s->cache, s->n_cache, pkt)) < 0)
        goto done;

    res = av_packet_copy_props(pkt, s->cache[s->n_cache - 1]);
    if (res < 0)
        goto done;

    for (n = 0; n < s->n_cache; n++)
        av_packet_unref(s->cache[n]);
    s->n_cache = 0;

done:
    if (res < 0)
        av_packet_unref(pkt);
    return res;
}