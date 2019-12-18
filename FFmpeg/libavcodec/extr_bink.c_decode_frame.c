#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_1__* priv_data; } ;
struct TYPE_11__ {int size; int /*<<< orphan*/  data; } ;
struct TYPE_10__ {char version; int frame_num; int /*<<< orphan*/ * last; int /*<<< orphan*/  swap_planes; scalar_t__ has_alpha; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_1__ BinkContext ;
typedef  TYPE_2__ AVPacket ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_GET_BUFFER_FLAG_REF ; 
 int av_frame_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_frame_unref (int /*<<< orphan*/ *) ; 
 int bink_decode_plane (TYPE_1__* const,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int binkb_decode_plane (TYPE_1__* const,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  emms_c () ; 
 int ff_get_buffer (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ff_reget_buffer (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_get_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skip_bits_long (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int decode_frame(AVCodecContext *avctx, void *data, int *got_frame, AVPacket *pkt)
{
    BinkContext * const c = avctx->priv_data;
    AVFrame *frame = data;
    GetBitContext gb;
    int plane, plane_idx, ret;
    int bits_count = pkt->size << 3;

    if (c->version > 'b') {
        if ((ret = ff_get_buffer(avctx, frame, AV_GET_BUFFER_FLAG_REF)) < 0)
            return ret;
    } else {
        if ((ret = ff_reget_buffer(avctx, c->last, 0)) < 0)
            return ret;
        if ((ret = av_frame_ref(frame, c->last)) < 0)
            return ret;
    }

    init_get_bits(&gb, pkt->data, bits_count);
    if (c->has_alpha) {
        if (c->version >= 'i')
            skip_bits_long(&gb, 32);
        if ((ret = bink_decode_plane(c, frame, &gb, 3, 0)) < 0)
            return ret;
    }
    if (c->version >= 'i')
        skip_bits_long(&gb, 32);

    c->frame_num++;

    for (plane = 0; plane < 3; plane++) {
        plane_idx = (!plane || !c->swap_planes) ? plane : (plane ^ 3);

        if (c->version > 'b') {
            if ((ret = bink_decode_plane(c, frame, &gb, plane_idx, !!plane)) < 0)
                return ret;
        } else {
            if ((ret = binkb_decode_plane(c, frame, &gb, plane_idx,
                                          c->frame_num == 1, !!plane)) < 0)
                return ret;
        }
        if (get_bits_count(&gb) >= bits_count)
            break;
    }
    emms_c();

    if (c->version > 'b') {
        av_frame_unref(c->last);
        if ((ret = av_frame_ref(c->last, frame)) < 0)
            return ret;
    }

    *got_frame = 1;

    /* always report that the buffer was completely consumed */
    return pkt->size;
}