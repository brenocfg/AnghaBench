#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int active_thread_type; } ;
struct TYPE_10__ {int /*<<< orphan*/  uni_chroma_ac_vlc_len; int /*<<< orphan*/  uni_ac_vlc_len; int /*<<< orphan*/  huff_size_ac_chrominance; int /*<<< orphan*/  huff_size_ac_luminance; } ;
struct TYPE_9__ {int mb_y; scalar_t__ huffman; int esc_pos; int mb_height; int* last_dc; int intra_dc_precision; TYPE_5__* avctx; int /*<<< orphan*/  pb; int /*<<< orphan*/  chroma_intra_matrix; int /*<<< orphan*/  intra_matrix; int /*<<< orphan*/  pred; int /*<<< orphan*/  intra_scantable; int /*<<< orphan*/  intra_chroma_ac_vlc_last_length; int /*<<< orphan*/  intra_chroma_ac_vlc_length; int /*<<< orphan*/  intra_ac_vlc_last_length; int /*<<< orphan*/  intra_ac_vlc_length; TYPE_2__* mjpeg_ctx; int /*<<< orphan*/  mb_x; } ;
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  TYPE_1__ MpegEncContext ;
typedef  TYPE_2__ MJpegContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int FF_THREAD_SLICE ; 
 scalar_t__ HUFFMAN_TABLE_OPTIMAL ; 
 scalar_t__ RST0 ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ff_init_uni_ac_vlc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_mjpeg_build_optimal_huffman (TYPE_2__*) ; 
 int /*<<< orphan*/  ff_mjpeg_encode_picture_frame (TYPE_1__*) ; 
 int /*<<< orphan*/  ff_mjpeg_encode_picture_header (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_mjpeg_escape_FF (int /*<<< orphan*/ *,int) ; 
 int ff_mpv_reallocate_putbitbuffer (TYPE_1__*,int,int) ; 
 int put_bits_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_marker (int /*<<< orphan*/ *,scalar_t__) ; 

int ff_mjpeg_encode_stuffing(MpegEncContext *s)
{
    int i;
    PutBitContext *pbc = &s->pb;
    int mb_y = s->mb_y - !s->mb_x;
    int ret;
    MJpegContext *m;

    m = s->mjpeg_ctx;

    if (s->huffman == HUFFMAN_TABLE_OPTIMAL) {
        ff_mjpeg_build_optimal_huffman(m);

        // Replace the VLCs with the optimal ones.
        // The default ones may be used for trellis during quantization.
        ff_init_uni_ac_vlc(m->huff_size_ac_luminance,   m->uni_ac_vlc_len);
        ff_init_uni_ac_vlc(m->huff_size_ac_chrominance, m->uni_chroma_ac_vlc_len);
        s->intra_ac_vlc_length      =
        s->intra_ac_vlc_last_length = m->uni_ac_vlc_len;
        s->intra_chroma_ac_vlc_length      =
        s->intra_chroma_ac_vlc_last_length = m->uni_chroma_ac_vlc_len;

        ff_mjpeg_encode_picture_header(s->avctx, &s->pb, &s->intra_scantable,
                                       s->pred, s->intra_matrix, s->chroma_intra_matrix);
        ff_mjpeg_encode_picture_frame(s);
    }

    ret = ff_mpv_reallocate_putbitbuffer(s, put_bits_count(&s->pb) / 8 + 100,
                                            put_bits_count(&s->pb) / 4 + 1000);

    if (ret < 0) {
        av_log(s->avctx, AV_LOG_ERROR, "Buffer reallocation failed\n");
        goto fail;
    }

    ff_mjpeg_escape_FF(pbc, s->esc_pos);

    if((s->avctx->active_thread_type & FF_THREAD_SLICE) && mb_y < s->mb_height)
        put_marker(pbc, RST0 + (mb_y&7));
    s->esc_pos = put_bits_count(pbc) >> 3;
fail:

    for(i=0; i<3; i++)
        s->last_dc[i] = 128 << s->intra_dc_precision;

    return ret;
}