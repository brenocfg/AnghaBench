#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_18__ {int /*<<< orphan*/  (* hevc_h_loop_filter_chroma ) (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* hevc_h_loop_filter_chroma_c ) (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* hevc_v_loop_filter_chroma ) (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* hevc_v_loop_filter_chroma_c ) (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* hevc_h_loop_filter_luma ) (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* hevc_h_loop_filter_luma_c ) (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* hevc_v_loop_filter_luma ) (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* hevc_v_loop_filter_luma_c ) (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_17__ {TYPE_4__* sps; TYPE_2__* pps; } ;
struct TYPE_20__ {int* vertical_bs; int bs_width; int* horizontal_bs; TYPE_7__* frame; TYPE_6__ hevcdsp; TYPE_5__ ps; TYPE_3__* deblock; } ;
struct TYPE_19__ {int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_13__ {scalar_t__ loop_filter_disable_flag; } ;
struct TYPE_16__ {int log2_ctb_size; int ctb_width; int width; int height; int pixel_shift; int* hshift; int* vshift; scalar_t__ chroma_format_idc; TYPE_1__ pcm; scalar_t__ pcm_enabled_flag; } ;
struct TYPE_15__ {int tc_offset; int beta_offset; } ;
struct TYPE_14__ {scalar_t__ transquant_bypass_enable_flag; } ;
typedef  TYPE_8__ HEVCContext ;

/* Variables and functions */
 size_t LUMA ; 
 int /*<<< orphan*/  MAX_QP ; 
 int /*<<< orphan*/  TC_CALC (int const,int const) ; 
 size_t av_clip (int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* betatable ; 
 int /*<<< orphan*/  chroma_tc (TYPE_8__*,int const,int,int) ; 
 int /*<<< orphan*/  get_pcm (TYPE_8__*,int,int) ; 
 int get_qPy (TYPE_8__*,int,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void deblocking_filter_CTB(HEVCContext *s, int x0, int y0)
{
    uint8_t *src;
    int x, y;
    int chroma, beta;
    int32_t c_tc[2], tc[2];
    uint8_t no_p[2] = { 0 };
    uint8_t no_q[2] = { 0 };

    int log2_ctb_size = s->ps.sps->log2_ctb_size;
    int x_end, x_end2, y_end;
    int ctb_size        = 1 << log2_ctb_size;
    int ctb             = (x0 >> log2_ctb_size) +
                          (y0 >> log2_ctb_size) * s->ps.sps->ctb_width;
    int cur_tc_offset   = s->deblock[ctb].tc_offset;
    int cur_beta_offset = s->deblock[ctb].beta_offset;
    int left_tc_offset, left_beta_offset;
    int tc_offset, beta_offset;
    int pcmf = (s->ps.sps->pcm_enabled_flag &&
                s->ps.sps->pcm.loop_filter_disable_flag) ||
               s->ps.pps->transquant_bypass_enable_flag;

    if (x0) {
        left_tc_offset   = s->deblock[ctb - 1].tc_offset;
        left_beta_offset = s->deblock[ctb - 1].beta_offset;
    } else {
        left_tc_offset   = 0;
        left_beta_offset = 0;
    }

    x_end = x0 + ctb_size;
    if (x_end > s->ps.sps->width)
        x_end = s->ps.sps->width;
    y_end = y0 + ctb_size;
    if (y_end > s->ps.sps->height)
        y_end = s->ps.sps->height;

    tc_offset   = cur_tc_offset;
    beta_offset = cur_beta_offset;

    x_end2 = x_end;
    if (x_end2 != s->ps.sps->width)
        x_end2 -= 8;
    for (y = y0; y < y_end; y += 8) {
        // vertical filtering luma
        for (x = x0 ? x0 : 8; x < x_end; x += 8) {
            const int bs0 = s->vertical_bs[(x +  y      * s->bs_width) >> 2];
            const int bs1 = s->vertical_bs[(x + (y + 4) * s->bs_width) >> 2];
            if (bs0 || bs1) {
                const int qp = (get_qPy(s, x - 1, y)     + get_qPy(s, x, y)     + 1) >> 1;

                beta = betatable[av_clip(qp + beta_offset, 0, MAX_QP)];

                tc[0]   = bs0 ? TC_CALC(qp, bs0) : 0;
                tc[1]   = bs1 ? TC_CALC(qp, bs1) : 0;
                src     = &s->frame->data[LUMA][y * s->frame->linesize[LUMA] + (x << s->ps.sps->pixel_shift)];
                if (pcmf) {
                    no_p[0] = get_pcm(s, x - 1, y);
                    no_p[1] = get_pcm(s, x - 1, y + 4);
                    no_q[0] = get_pcm(s, x, y);
                    no_q[1] = get_pcm(s, x, y + 4);
                    s->hevcdsp.hevc_v_loop_filter_luma_c(src,
                                                         s->frame->linesize[LUMA],
                                                         beta, tc, no_p, no_q);
                } else
                    s->hevcdsp.hevc_v_loop_filter_luma(src,
                                                       s->frame->linesize[LUMA],
                                                       beta, tc, no_p, no_q);
            }
        }

        if(!y)
             continue;

        // horizontal filtering luma
        for (x = x0 ? x0 - 8 : 0; x < x_end2; x += 8) {
            const int bs0 = s->horizontal_bs[( x      + y * s->bs_width) >> 2];
            const int bs1 = s->horizontal_bs[((x + 4) + y * s->bs_width) >> 2];
            if (bs0 || bs1) {
                const int qp = (get_qPy(s, x, y - 1)     + get_qPy(s, x, y)     + 1) >> 1;

                tc_offset   = x >= x0 ? cur_tc_offset : left_tc_offset;
                beta_offset = x >= x0 ? cur_beta_offset : left_beta_offset;

                beta = betatable[av_clip(qp + beta_offset, 0, MAX_QP)];
                tc[0]   = bs0 ? TC_CALC(qp, bs0) : 0;
                tc[1]   = bs1 ? TC_CALC(qp, bs1) : 0;
                src     = &s->frame->data[LUMA][y * s->frame->linesize[LUMA] + (x << s->ps.sps->pixel_shift)];
                if (pcmf) {
                    no_p[0] = get_pcm(s, x, y - 1);
                    no_p[1] = get_pcm(s, x + 4, y - 1);
                    no_q[0] = get_pcm(s, x, y);
                    no_q[1] = get_pcm(s, x + 4, y);
                    s->hevcdsp.hevc_h_loop_filter_luma_c(src,
                                                         s->frame->linesize[LUMA],
                                                         beta, tc, no_p, no_q);
                } else
                    s->hevcdsp.hevc_h_loop_filter_luma(src,
                                                       s->frame->linesize[LUMA],
                                                       beta, tc, no_p, no_q);
            }
        }
    }

    if (s->ps.sps->chroma_format_idc) {
        for (chroma = 1; chroma <= 2; chroma++) {
            int h = 1 << s->ps.sps->hshift[chroma];
            int v = 1 << s->ps.sps->vshift[chroma];

            // vertical filtering chroma
            for (y = y0; y < y_end; y += (8 * v)) {
                for (x = x0 ? x0 : 8 * h; x < x_end; x += (8 * h)) {
                    const int bs0 = s->vertical_bs[(x +  y            * s->bs_width) >> 2];
                    const int bs1 = s->vertical_bs[(x + (y + (4 * v)) * s->bs_width) >> 2];

                    if ((bs0 == 2) || (bs1 == 2)) {
                        const int qp0 = (get_qPy(s, x - 1, y)           + get_qPy(s, x, y)           + 1) >> 1;
                        const int qp1 = (get_qPy(s, x - 1, y + (4 * v)) + get_qPy(s, x, y + (4 * v)) + 1) >> 1;

                        c_tc[0] = (bs0 == 2) ? chroma_tc(s, qp0, chroma, tc_offset) : 0;
                        c_tc[1] = (bs1 == 2) ? chroma_tc(s, qp1, chroma, tc_offset) : 0;
                        src       = &s->frame->data[chroma][(y >> s->ps.sps->vshift[chroma]) * s->frame->linesize[chroma] + ((x >> s->ps.sps->hshift[chroma]) << s->ps.sps->pixel_shift)];
                        if (pcmf) {
                            no_p[0] = get_pcm(s, x - 1, y);
                            no_p[1] = get_pcm(s, x - 1, y + (4 * v));
                            no_q[0] = get_pcm(s, x, y);
                            no_q[1] = get_pcm(s, x, y + (4 * v));
                            s->hevcdsp.hevc_v_loop_filter_chroma_c(src,
                                                                   s->frame->linesize[chroma],
                                                                   c_tc, no_p, no_q);
                        } else
                            s->hevcdsp.hevc_v_loop_filter_chroma(src,
                                                                 s->frame->linesize[chroma],
                                                                 c_tc, no_p, no_q);
                    }
                }

                if(!y)
                    continue;

                // horizontal filtering chroma
                tc_offset = x0 ? left_tc_offset : cur_tc_offset;
                x_end2 = x_end;
                if (x_end != s->ps.sps->width)
                    x_end2 = x_end - 8 * h;
                for (x = x0 ? x0 - 8 * h : 0; x < x_end2; x += (8 * h)) {
                    const int bs0 = s->horizontal_bs[( x          + y * s->bs_width) >> 2];
                    const int bs1 = s->horizontal_bs[((x + 4 * h) + y * s->bs_width) >> 2];
                    if ((bs0 == 2) || (bs1 == 2)) {
                        const int qp0 = bs0 == 2 ? (get_qPy(s, x,           y - 1) + get_qPy(s, x,           y) + 1) >> 1 : 0;
                        const int qp1 = bs1 == 2 ? (get_qPy(s, x + (4 * h), y - 1) + get_qPy(s, x + (4 * h), y) + 1) >> 1 : 0;

                        c_tc[0]   = bs0 == 2 ? chroma_tc(s, qp0, chroma, tc_offset)     : 0;
                        c_tc[1]   = bs1 == 2 ? chroma_tc(s, qp1, chroma, cur_tc_offset) : 0;
                        src       = &s->frame->data[chroma][(y >> s->ps.sps->vshift[1]) * s->frame->linesize[chroma] + ((x >> s->ps.sps->hshift[1]) << s->ps.sps->pixel_shift)];
                        if (pcmf) {
                            no_p[0] = get_pcm(s, x,           y - 1);
                            no_p[1] = get_pcm(s, x + (4 * h), y - 1);
                            no_q[0] = get_pcm(s, x,           y);
                            no_q[1] = get_pcm(s, x + (4 * h), y);
                            s->hevcdsp.hevc_h_loop_filter_chroma_c(src,
                                                                   s->frame->linesize[chroma],
                                                                   c_tc, no_p, no_q);
                        } else
                            s->hevcdsp.hevc_h_loop_filter_chroma(src,
                                                                 s->frame->linesize[chroma],
                                                                 c_tc, no_p, no_q);
                    }
                }
            }
        }
    }
}