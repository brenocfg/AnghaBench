#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* h263_h_loop_filter ) (int /*<<< orphan*/ *,int const,int const) ;int /*<<< orphan*/  (* h263_v_loop_filter ) (int /*<<< orphan*/ *,int const,int const) ;} ;
struct TYPE_5__ {int* qscale_table; int /*<<< orphan*/ * mb_type; } ;
struct TYPE_7__ {int linesize; int uvlinesize; int mb_y; int mb_stride; int mb_x; int qscale; int* chroma_qscale_table; int mb_height; TYPE_2__ h263dsp; TYPE_1__ current_picture; int /*<<< orphan*/ ** dest; } ;
typedef  TYPE_3__ MpegEncContext ;

/* Variables and functions */
 scalar_t__ IS_SKIP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int const,int) ; 
 int /*<<< orphan*/  stub10 (int /*<<< orphan*/ *,int const,int const) ; 
 int /*<<< orphan*/  stub11 (int /*<<< orphan*/ *,int const,int) ; 
 int /*<<< orphan*/  stub12 (int /*<<< orphan*/ *,int const,int) ; 
 int /*<<< orphan*/  stub13 (int /*<<< orphan*/ *,int const,int) ; 
 int /*<<< orphan*/  stub14 (int /*<<< orphan*/ *,int const,int) ; 
 int /*<<< orphan*/  stub15 (int /*<<< orphan*/ *,int const,int const) ; 
 int /*<<< orphan*/  stub16 (int /*<<< orphan*/ *,int const,int const) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int const,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int const,int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *,int const,int) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ *,int const,int const) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ *,int const,int const) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ *,int const,int) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ *,int const,int) ; 
 int /*<<< orphan*/  stub9 (int /*<<< orphan*/ *,int const,int const) ; 

void ff_h263_loop_filter(MpegEncContext * s){
    int qp_c;
    const int linesize  = s->linesize;
    const int uvlinesize= s->uvlinesize;
    const int xy = s->mb_y * s->mb_stride + s->mb_x;
    uint8_t *dest_y = s->dest[0];
    uint8_t *dest_cb= s->dest[1];
    uint8_t *dest_cr= s->dest[2];

    /*
       Diag Top
       Left Center
    */
    if (!IS_SKIP(s->current_picture.mb_type[xy])) {
        qp_c= s->qscale;
        s->h263dsp.h263_v_loop_filter(dest_y + 8 * linesize,     linesize, qp_c);
        s->h263dsp.h263_v_loop_filter(dest_y + 8 * linesize + 8, linesize, qp_c);
    }else
        qp_c= 0;

    if(s->mb_y){
        int qp_dt, qp_tt, qp_tc;

        if (IS_SKIP(s->current_picture.mb_type[xy - s->mb_stride]))
            qp_tt=0;
        else
            qp_tt = s->current_picture.qscale_table[xy - s->mb_stride];

        if(qp_c)
            qp_tc= qp_c;
        else
            qp_tc= qp_tt;

        if(qp_tc){
            const int chroma_qp= s->chroma_qscale_table[qp_tc];
            s->h263dsp.h263_v_loop_filter(dest_y,     linesize, qp_tc);
            s->h263dsp.h263_v_loop_filter(dest_y + 8, linesize, qp_tc);

            s->h263dsp.h263_v_loop_filter(dest_cb, uvlinesize, chroma_qp);
            s->h263dsp.h263_v_loop_filter(dest_cr, uvlinesize, chroma_qp);
        }

        if(qp_tt)
            s->h263dsp.h263_h_loop_filter(dest_y - 8 * linesize + 8, linesize, qp_tt);

        if(s->mb_x){
            if (qp_tt || IS_SKIP(s->current_picture.mb_type[xy - 1 - s->mb_stride]))
                qp_dt= qp_tt;
            else
                qp_dt = s->current_picture.qscale_table[xy - 1 - s->mb_stride];

            if(qp_dt){
                const int chroma_qp= s->chroma_qscale_table[qp_dt];
                s->h263dsp.h263_h_loop_filter(dest_y  - 8 * linesize,   linesize,   qp_dt);
                s->h263dsp.h263_h_loop_filter(dest_cb - 8 * uvlinesize, uvlinesize, chroma_qp);
                s->h263dsp.h263_h_loop_filter(dest_cr - 8 * uvlinesize, uvlinesize, chroma_qp);
            }
        }
    }

    if(qp_c){
        s->h263dsp.h263_h_loop_filter(dest_y + 8, linesize, qp_c);
        if(s->mb_y + 1 == s->mb_height)
            s->h263dsp.h263_h_loop_filter(dest_y + 8 * linesize + 8, linesize, qp_c);
    }

    if(s->mb_x){
        int qp_lc;
        if (qp_c || IS_SKIP(s->current_picture.mb_type[xy - 1]))
            qp_lc= qp_c;
        else
            qp_lc = s->current_picture.qscale_table[xy - 1];

        if(qp_lc){
            s->h263dsp.h263_h_loop_filter(dest_y, linesize, qp_lc);
            if(s->mb_y + 1 == s->mb_height){
                const int chroma_qp= s->chroma_qscale_table[qp_lc];
                s->h263dsp.h263_h_loop_filter(dest_y + 8 * linesize, linesize, qp_lc);
                s->h263dsp.h263_h_loop_filter(dest_cb, uvlinesize, chroma_qp);
                s->h263dsp.h263_h_loop_filter(dest_cr, uvlinesize, chroma_qp);
            }
        }
    }
}