#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  (* qpel_mc_func ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int const) ;
typedef  int /*<<< orphan*/  (* h264_chroma_mc_func ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int const,int,int) ;
typedef  int /*<<< orphan*/  ThreadFrame ;
struct TYPE_20__ {int /*<<< orphan*/  (* emulated_edge_mc ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int const,int const,int,int,int,int) ;} ;
struct TYPE_19__ {int /*<<< orphan*/ * edge_emu_buffer; } ;
struct TYPE_12__ {int mb_x; int mb_y; int b8_stride; int linesize; int uvlinesize; int const h_edge_pos; int const v_edge_pos; TYPE_8__ vdsp; TYPE_7__ sc; int /*<<< orphan*/ ** dest; TYPE_6__* last_picture_ptr; TYPE_4__* next_picture_ptr; TYPE_2__* avctx; TYPE_1__* current_picture_ptr; } ;
struct TYPE_21__ {int /*<<< orphan*/ ** tmp_b_block_uv; int /*<<< orphan*/ ** tmp_b_block_y; TYPE_10__ s; } ;
struct TYPE_18__ {TYPE_5__* f; int /*<<< orphan*/  tf; } ;
struct TYPE_17__ {int /*<<< orphan*/ ** data; } ;
struct TYPE_16__ {TYPE_3__* f; int /*<<< orphan*/  tf; } ;
struct TYPE_15__ {int /*<<< orphan*/ ** data; } ;
struct TYPE_14__ {int active_thread_type; } ;
struct TYPE_13__ {int*** motion_val; } ;
typedef  TYPE_9__ RV34DecContext ;
typedef  TYPE_10__ MpegEncContext ;

/* Variables and functions */
 int FF_THREAD_FRAME ; 
 scalar_t__ HAVE_THREADS ; 
 int const RV34_MB_P_16x8 ; 
 int const RV34_MB_P_8x16 ; 
 int const RV34_MB_P_8x8 ; 
 int* chroma_coeffs ; 
 int /*<<< orphan*/  ff_thread_await_progress (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int const,int const,int,int,int,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int const,int const,int const,int const,int,int,int,int) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int const,int const,int,int,int,int) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int const,int,int) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int const,int,int) ; 

__attribute__((used)) static inline void rv34_mc(RV34DecContext *r, const int block_type,
                          const int xoff, const int yoff, int mv_off,
                          const int width, const int height, int dir,
                          const int thirdpel, int weighted,
                          qpel_mc_func (*qpel_mc)[16],
                          h264_chroma_mc_func (*chroma_mc))
{
    MpegEncContext *s = &r->s;
    uint8_t *Y, *U, *V, *srcY, *srcU, *srcV;
    int dxy, mx, my, umx, umy, lx, ly, uvmx, uvmy, src_x, src_y, uvsrc_x, uvsrc_y;
    int mv_pos = s->mb_x * 2 + s->mb_y * 2 * s->b8_stride + mv_off;
    int is16x16 = 1;
    int emu = 0;

    if(thirdpel){
        int chroma_mx, chroma_my;
        mx = (s->current_picture_ptr->motion_val[dir][mv_pos][0] + (3 << 24)) / 3 - (1 << 24);
        my = (s->current_picture_ptr->motion_val[dir][mv_pos][1] + (3 << 24)) / 3 - (1 << 24);
        lx = (s->current_picture_ptr->motion_val[dir][mv_pos][0] + (3 << 24)) % 3;
        ly = (s->current_picture_ptr->motion_val[dir][mv_pos][1] + (3 << 24)) % 3;
        chroma_mx = s->current_picture_ptr->motion_val[dir][mv_pos][0] / 2;
        chroma_my = s->current_picture_ptr->motion_val[dir][mv_pos][1] / 2;
        umx = (chroma_mx + (3 << 24)) / 3 - (1 << 24);
        umy = (chroma_my + (3 << 24)) / 3 - (1 << 24);
        uvmx = chroma_coeffs[(chroma_mx + (3 << 24)) % 3];
        uvmy = chroma_coeffs[(chroma_my + (3 << 24)) % 3];
    }else{
        int cx, cy;
        mx = s->current_picture_ptr->motion_val[dir][mv_pos][0] >> 2;
        my = s->current_picture_ptr->motion_val[dir][mv_pos][1] >> 2;
        lx = s->current_picture_ptr->motion_val[dir][mv_pos][0] & 3;
        ly = s->current_picture_ptr->motion_val[dir][mv_pos][1] & 3;
        cx = s->current_picture_ptr->motion_val[dir][mv_pos][0] / 2;
        cy = s->current_picture_ptr->motion_val[dir][mv_pos][1] / 2;
        umx = cx >> 2;
        umy = cy >> 2;
        uvmx = (cx & 3) << 1;
        uvmy = (cy & 3) << 1;
        //due to some flaw RV40 uses the same MC compensation routine for H2V2 and H3V3
        if(uvmx == 6 && uvmy == 6)
            uvmx = uvmy = 4;
    }

    if (HAVE_THREADS && (s->avctx->active_thread_type & FF_THREAD_FRAME)) {
        /* wait for the referenced mb row to be finished */
        int mb_row = s->mb_y + ((yoff + my + 5 + 8 * height) >> 4);
        ThreadFrame *f = dir ? &s->next_picture_ptr->tf : &s->last_picture_ptr->tf;
        ff_thread_await_progress(f, mb_row, 0);
    }

    dxy = ly*4 + lx;
    srcY = dir ? s->next_picture_ptr->f->data[0] : s->last_picture_ptr->f->data[0];
    srcU = dir ? s->next_picture_ptr->f->data[1] : s->last_picture_ptr->f->data[1];
    srcV = dir ? s->next_picture_ptr->f->data[2] : s->last_picture_ptr->f->data[2];
    src_x = s->mb_x * 16 + xoff + mx;
    src_y = s->mb_y * 16 + yoff + my;
    uvsrc_x = s->mb_x * 8 + (xoff >> 1) + umx;
    uvsrc_y = s->mb_y * 8 + (yoff >> 1) + umy;
    srcY += src_y * s->linesize + src_x;
    srcU += uvsrc_y * s->uvlinesize + uvsrc_x;
    srcV += uvsrc_y * s->uvlinesize + uvsrc_x;
    if(s->h_edge_pos - (width << 3) < 6 || s->v_edge_pos - (height << 3) < 6 ||
       (unsigned)(src_x - !!lx*2) > s->h_edge_pos - !!lx*2 - (width <<3) - 4 ||
       (unsigned)(src_y - !!ly*2) > s->v_edge_pos - !!ly*2 - (height<<3) - 4) {
        srcY -= 2 + 2*s->linesize;
        s->vdsp.emulated_edge_mc(s->sc.edge_emu_buffer, srcY,
                                 s->linesize, s->linesize,
                                 (width << 3) + 6, (height << 3) + 6,
                                 src_x - 2, src_y - 2,
                                 s->h_edge_pos, s->v_edge_pos);
        srcY = s->sc.edge_emu_buffer + 2 + 2*s->linesize;
        emu = 1;
    }
    if(!weighted){
        Y = s->dest[0] + xoff      + yoff     *s->linesize;
        U = s->dest[1] + (xoff>>1) + (yoff>>1)*s->uvlinesize;
        V = s->dest[2] + (xoff>>1) + (yoff>>1)*s->uvlinesize;
    }else{
        Y = r->tmp_b_block_y [dir]     +  xoff     +  yoff    *s->linesize;
        U = r->tmp_b_block_uv[dir*2]   + (xoff>>1) + (yoff>>1)*s->uvlinesize;
        V = r->tmp_b_block_uv[dir*2+1] + (xoff>>1) + (yoff>>1)*s->uvlinesize;
    }

    if(block_type == RV34_MB_P_16x8){
        qpel_mc[1][dxy](Y, srcY, s->linesize);
        Y    += 8;
        srcY += 8;
    }else if(block_type == RV34_MB_P_8x16){
        qpel_mc[1][dxy](Y, srcY, s->linesize);
        Y    += 8 * s->linesize;
        srcY += 8 * s->linesize;
    }
    is16x16 = (block_type != RV34_MB_P_8x8) && (block_type != RV34_MB_P_16x8) && (block_type != RV34_MB_P_8x16);
    qpel_mc[!is16x16][dxy](Y, srcY, s->linesize);
    if (emu) {
        uint8_t *uvbuf = s->sc.edge_emu_buffer;

        s->vdsp.emulated_edge_mc(uvbuf, srcU,
                                 s->uvlinesize, s->uvlinesize,
                                 (width << 2) + 1, (height << 2) + 1,
                                 uvsrc_x, uvsrc_y,
                                 s->h_edge_pos >> 1, s->v_edge_pos >> 1);
        srcU = uvbuf;
        uvbuf += 9*s->uvlinesize;

        s->vdsp.emulated_edge_mc(uvbuf, srcV,
                                 s->uvlinesize, s->uvlinesize,
                                 (width << 2) + 1, (height << 2) + 1,
                                 uvsrc_x, uvsrc_y,
                                 s->h_edge_pos >> 1, s->v_edge_pos >> 1);
        srcV = uvbuf;
    }
    chroma_mc[2-width]   (U, srcU, s->uvlinesize, height*4, uvmx, uvmy);
    chroma_mc[2-width]   (V, srcV, s->uvlinesize, height*4, uvmx, uvmy);
}